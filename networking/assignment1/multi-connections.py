import socket
import selectors
import types
import sys

sel = selectors.DefaultSelector()

host, port = sys.argv[1], int(sys.argv[2])
lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


# Simple Event loop
try:
    while True:
        events = sel.select(timeout=None)
        

