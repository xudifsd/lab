package main

import (
    "time"
    "fmt"
)

func service1() chan string {
    result := make(chan string)
    go func() {
        defer close(result)
        for _, num := range []int{1,2,3,4,5,6} {
            time.Sleep(1 * time.Second)
            result <- fmt.Sprintf("%d from service1", num)
        }
    }()
    return result
}

func service2() chan string {
    result := make(chan string)
    go func() {
        defer close(result)
        for _, num := range []int{1,2,3,4,5,6} {
            time.Sleep(2 * time.Second)
            result <- fmt.Sprintf("%d from service2", num)
        }
    }()
    return result
}

func main() {
    chan1 := service1()
    chan2 := service1()
    num := 2
    for {
        select {
        case v, ok := <- chan1:
            if ok {
                fmt.Printf("main received from c1 '%s'\n", v)
            } else {
                num -= 1
            }
        case v, ok := <- chan2:
            if ok {
                fmt.Printf("main received from c2 '%s'\n", v)
            } else {
                num -= 1
            }
        }
        if num == 0 {
            break
        }
    }
}
