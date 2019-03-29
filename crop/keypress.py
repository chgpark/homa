import threading, time, curses

class keyinput:
    def __init__(self):
        self.input = ""
        threading.Thread(target=self.thread1).start()

    def fn_key(self, win):
        win.nodelay(True)
        win.clear()
        while 1:
            try:
                key = win.getkey()
                win.refresh
                if str(key) == 'q':
                    self.input = str(key)
                win.clear()
                time.sleep(1)

            except Exception as e:
                self.input = None
                pass

    def thread1(self):
        self.lock = threading.Lock()
        curses.wrapper(self.fn_key)

if __name__ == '__main__':
    ke = keyinput()
    while True:
        print(ke.input)
        time.sleep(1)
