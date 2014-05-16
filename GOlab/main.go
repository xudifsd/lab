package main

import (
    "./list"
    "fmt"
)

func main() {
    var head *list.Node
    list.ListInsert(&head, 2)
    list.ListInsert(&head, 20)
    list.ListInsert(&head, 100)
    list.ListInsert(&head, 3)
    list.ListInsert(&head, 5)

    list.ListTraverse(head, func (p *list.Node) {
                                fmt.Printf("%d, ", p.Value)
                            })
    fmt.Println("")
}
