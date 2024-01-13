# CURL Clone in Python

import socket
import sys

# The server's hostname or IP address
# HOST = "http://insecure.stevetarzia.com/basic.html"
HOST = "http://insecure.stevetarzia.com/redirect"
PORT = 80  # The port used by the server

ttt = 0


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def connecttoUrl(url, port=80):
    response = ""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        double_slash_index = url.find("//")
        # Find the index of the next slash after the double slash
        next_slash_index = url.find("/", double_slash_index + 2)
        # Extract the domain and URI
        domain = url[double_slash_index + 2:next_slash_index]
        path = url[next_slash_index:]
        hostno = socket.gethostbyname(domain)
        s.connect((hostno, port))
        # s.sendall(b"Hello, world")
        request = f"GET {path} HTTP/1.1\r\nHost: {domain}\r\n\r\n"
        s.sendall(request.encode())
        while True:
            data = s.recv(1024).decode()
            if not data:
                break
            response = response + data
        response_list = response.split()
    if '301 Moved Permanently' in response or '302 Found' in response:
        if ttt > 10:
            eprint(f'Infinite Loop')
            return
        ttt += 1
        newIndex = response_list.index('Location:')
        eprint(f'Redirected to {response_list[newIndex+1]}')
        return connecttoUrl(response_list[newIndex+1], PORT)
    else:
        doctype_index = response.find('<!DOCTYPE>')
        # Print the content after <!DOCTYPE>
        # if doctype_index != -1:
        #     print(response[doctype_index + len('<!DOCTYPE'):])
        return True, response[doctype_index + len('<!DOCTYPE'):]


success, data = connecttoUrl(sys.argv[1], PORT)
print(f"{data}")
