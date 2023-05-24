import requests

rhost = "http://localhost:"
red = "\033[0;31m"
green = "\033[0;32m"
blue = "\033[0;34m"
nc = "\033[0m"

def cgiRequest(port, uri, expected, expectedBody = False, contentLength = False, query = False):
    if query == False:
        print(red + "GET " + rhost + str(port) + uri + nc)
    else:
        print(red + "GET " + rhost + str(port) + uri + "?", end = "")
        n = 1
        for i in query.keys():
            print(i + "=" + query[i], end = "")
            if n == len(query.keys()):
                print()
            else:
                print("&", end = "")
            n += 1
    print(green + "Expected: " + expected + nc)
    if query == False:
        r = requests.get(rhost + str(port) + uri)
    else:
        r = requests.get(rhost + str(port) + uri, query)
    print(blue + "I received:" + nc)
    print("Status Code: " + str(r.status_code))
    for h in r.headers:
        print(h + ":" + r.headers[h])
    print()
    if contentLength == False:
        print(r.text)
    else:
        print("Body not displayed as it is too long")



def cgi(port):
    pages = [
            ["/YoupiBanane/youpi.bla", "Content of hello.sh", "Hello\n", False, False],
            ["/YoupiBanane/index.php", "Content of hello.sh", "Hello\n", False, False]
        ]
    for page in pages:
        cgiRequest(port, page[0], page[1], page[2], page[3], page[4])
        input("Press Enter: ")


cgi(8080)