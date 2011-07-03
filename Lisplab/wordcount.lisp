;;; This is the first version of wordcount in lisp, because of limit of recursion in clisp is 7000+,
;;; this program can't count file line amount exceed 1000. This program will read file in *filename*, you can
;;; use this program like "time clisp wordcount.lisp 2>/dev/null |grep -v "^;" | sort -k1,1nr -k2|head -n 10"

(defun new-node(string count left right)
	`(,string ,count ,left . ,right))

(defun insert(head string)	;functional promgraming style
	(cond
	 	((null head)
			(new-node string 1 nil nil))
		((string< (car head) string)
			(new-node (car head) (cadr head) (caddr head) (insert (cdddr head) string)))
		((string> (car head) string)
			(new-node (car head) (cadr head) (insert (caddr head) string) (cdddr head)))
		((string= (car head) string)
			(new-node (car head) (1+ (cadr head)) (caddr head) (cdddr head)))))

(defun print-all (head)
	(if (null head)
		nil
		(progn
			(print-all (caddr head))
			(format t "~%~A ~A" (cadr head) (car head))
			(print-all (cdddr head)))))

(defun insert-with-list (head word-list)	;functional promgraming style
	(if (null word-list)
		head
		(insert (insert-with-list head (cdr word-list)) (car word-list))))

(asdf:load-system "cl-ppcre")	;insert-with-stream need cl-ppcre

(defun insert-with-stream (head stream)	;functional promgraming style
	(let ((line (read-line stream nil 'eof)))
		(if (eql line 'eof)
			head
			(insert-with-list (insert-with-stream head stream) (cl-ppcre:all-matches-as-strings "\\w+" line)))))

(setf *filename* "part.txt")

(print-all (with-open-file (stream *filename* :direction :input)
	(insert-with-stream nil stream)))

