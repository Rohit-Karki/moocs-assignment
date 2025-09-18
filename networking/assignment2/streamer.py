# do not import anything else from loss_socket besides LossyUDP
from lossy_socket import LossyUDP
# do not import anything else from socket except INADDR_ANY
from socket import INADDR_ANY
import time
from concurrent.futures import ThreadPoolExecutor
from TCPpacket import TCPpacket


class Streamer:
    send_seqeunce_no = 0
    receive_sequence_number = 0

    send_buffer = {}
    receive_buffer = {}

    self_half_closed = False
    remote_closed = False
    closed = False

    executor = None
    recv_thread = None
    send_thread = None

    chunk_size = 1446
    time_out_seconds = 0.25
    fin_grace_period = 2
    default_wait_seconds = 0.001

    def __init__(self, dst_ip, dst_port,
                 src_ip=INADDR_ANY, src_port=0):
        """Default values listen on all network interfaces, chooses a random source port,
           and does not introduce any simulated packet loss."""
        self.socket = LossyUDP()
        self.socket.bind((src_ip, src_port))
        self.dst_ip = dst_ip
        self.dst_port = dst_port
        self.sequence_no = 0

        self.executor = ThreadPoolExecutor(max_workers=1)
        self.recv_thread = self.executor.submit(self.recv_async)
        self.send_thread = self.executor.submit(self.send_async)

    def send(self, data_bytes: bytes) -> None:
        """Note that data_bytes can be larger than one packet."""
        # Your code goes here!  The code below should be changed!
        chunk_index = 0
        while chunk_index * self.chunk_size < len(data_bytes):
            chunk_start_index = chunk_index * self.chunk_size
            chunk_end_index = min(
                len(data_bytes), (chunk_index + 1) * self.chunk_size)

            packet = TCPpacket(sequence_no=self.send_seqeunce_no,
                               data_bytes=data_bytes[chunk_start_index:chunk_end_index])
            print(f"{packet}")
            self.send_buffer[self.send_seqeunce_no] = packet

            self.socket.sendto(packet.pack(), (self.dst_ip, self.dst_port))
            self.send_seqeunce_no += 1
            chunk_index += 1
    
    def send_ack(self, ack_sequence_np: int):
        packet = TCPpacket(sequence_no=ack_sequence_np, ack=True)
        self.socket.sendto(packet.pack(), (self.dst_ip, self.dst_port))
    
    def send_async(self):
        # Here we check if we got an ack for previous sent packets and resend if we did not get an ack
        while not self.closed:
            try:
                data, addr = self.socket.recvfrom()
                if data is not None and data != b'':
                    packet = TCPpacket()
                    packet.unpack(data)

                    if packet.sequence_no not in self.receive_buffer:
                        # It means that we have not received this packet before
                        self.receive_buffer[packet.sequence_no] = packet

                    print(f"{self.receive_buffer}")
            except Exception as e:
                print("listener died!")
                print(e)

    def recv(self) -> bytes:
        """Blocks (waits) if no data is ready to be read from the connection."""
        while self.receive_sequence_number not in self.receive_buffer:
            time.sleep(self.default_wait_seconds)
        print(f"{self.receive_buffer}")

        curr = self.receive_buffer[self.receive_sequence_number]
        del self.receive_buffer[self.receive_sequence_number]
        # now send the ACK packet to the sender

        print(f"{curr}")
        self.receive_sequence_number += 1
        return curr.data_bytes

    def recv_async(self):
        while not self.closed:
            try:
                data, addr = self.socket.recvfrom()
                if data is not None and data != b'':
                    packet = TCPpacket()
                    packet.unpack(data)


                    if packet.ack:
                        # this packet is an ACK packet so we can send the next packet
                        self.send
                        if packet.sequence_no not in self.receive_buffer:
                            # It means that we have not received this packet before
                            self.receive_buffer[packet.sequence_no] = packet

                    print(f"{self.receive_buffer}")
            except Exception as e:
                print("listener died!")
                print(e)
    

    def close(self) -> None:
        """Cleans up. It should block (wait) until the Streamer is done with all
           the necessary ACKs and retransmissions"""
        # your code goes here, especially after you add ACKs and retransmissions.
        self.closed = True
        self.socket.stoprecv()

        while not self.recv_thread.done():
            self.recv_thread.cancel()
            time.sleep(self.default_wait_seconds)

        self.executor.shutdown()
        pass
