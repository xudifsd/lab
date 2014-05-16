package list

type Node struct {
    Value int
    Next *Node
}

func ListInsert(head **Node, value int) {
    p := *head
    for ; p != nil; head, p = &p.Next, p.Next {
        if (p.Value >= value) {
            break
        }
    }
    *head = new(Node)
    (*head).Value = value
    (*head).Next = p
}

func ListTraverse(head *Node, f func (*Node)) {
    for ; head != nil; head = head.Next {
        f(head)
    }
}
