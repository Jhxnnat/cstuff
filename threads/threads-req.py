import threading
import time
from urllib.request import urlopen, Request

links = [
    "https://python.org",
    "https://gnome.org",
    "https://debian.org",
    "https://archlinux.org",
]

def threadfunc(link):
    if "python" in link:
        time.sleep(3)
    print(f"> request for {link}")
    req = Request(link, headers={"Accept": "application/json"})
    with urlopen(req) as res:
        print(f"  response for {link}: {res.status}")

threads = []
for l in links:
    _t = threading.Thread(target=threadfunc, args=(l,))
    threads.append(_t)

for t in threads:
    t.start()
for t in threads:
    t.join()
