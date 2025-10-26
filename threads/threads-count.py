import threading
import time

thread_amount = 12
max_num = 1000000
count = 0

def loop(num):
    global count
    for _ in range(num):
        count += 1
    print(f"finished thread. count = {count}")

threads = []
for _ in range(thread_amount):
    _t = threading.Thread(target=loop, args=(max_num,))
    threads.append(_t)

start = time.time()
for t in threads:
    t.start()
for t in threads:
    t.join()
end = time.time()
clock = round(end - start, 2)

print(f"All theads finished in {clock}. count: {count}")
