import sys
from part1.http_get_handler import HttpHandler


def main(argv: list):
    if argv is None or len(argv) != 2:
        wrong_format()
    url = argv[1]
    if len(url) < 7 or url[0:7] != "http://":
        wrong_format()
    httpHandler = HttpHandler()
    response = httpHandler.get(url=url, recursion_count=10)
    print(response)


def wrong_format():
    sys.stderr.write('Correct Format:\ncurl.py http://<url>')
    sys.exit(2)
