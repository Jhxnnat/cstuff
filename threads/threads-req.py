import threading
import time
from urllib.request import urlopen, Request

links = [
    "https://python.org",
    "https://gnome.org",
    "https://debian.org",
    "https://archlinux.org",
    # "https://www.wikipedia.org/",
]

def threadfunc(link):
    if "python" in link:
        time.sleep(3)
    print(f"Network request started for {link}")
    req = Request(link, headers={"Accept": "application/json"})
    with urlopen(req) as res:
        print(f"    for link {link}    {res.status}")
    print(f"Network request ended for {link}")

threads = []
for l in links:
    _t = threading.Thread(target=threadfunc, args=(l,))
    threads.append(_t)

for t in threads:
    t.start()

for t in threads:
    t.join()
