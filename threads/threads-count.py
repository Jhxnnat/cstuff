import threading
import time

thread_amount = 3
max_num = 300000000
count = 0
mutex = threading.Lock()

def loop():
    global count
    while count < max_num:
        with mutex:
            count += 1

threads = []
for _ in range(thread_amount):
    _t = threading.Thread(target=loop)
    threads.append(_t)

start = time.time()
for t in threads:
    t.start()
for t in threads:
    t.join()
end = time.time()
clock = round(end - start, 2)
print(f"All theads finished in {clock}. count: {count}")

