package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

var (
	globalState int
	mutex       sync.Mutex
)

type testClass struct {
	secretValue int
}

func newTestClass() *testClass {
	return &testClass{
		secretValue: rand.Intn(100),
	}
}

func (h *testClass) test() string {
	time.Sleep(time.Duration(rand.Intn(100)) * time.Millisecond)
	return fmt.Sprintf("Secret: %d", h.secretValue)
}

func updateGlobalState(value int) {
	mutex.Lock()
	defer mutex.Unlock()
	globalState += value
}

func complexLogic() string {
	h := newHiddenClass()
	updateGlobalState(h.secretValue)
	return h.test()
}

func main() {
	fmt.Println(complexLogic())
}
