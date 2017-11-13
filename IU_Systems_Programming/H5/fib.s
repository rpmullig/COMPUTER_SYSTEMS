	.text
	.syntax unified
	.thumb
	.global	fib	
	.type fib, %function
fib:
	push {r4-r7}
/*
	Your implementation goes here. 
*/
	str	r0, [r7, #4]
	movs	r3, #1
	str	r3, [r7, #20]
	movs	r3, #1
	str	r3, [r7, #16]
	movs	r3, #1
	str	r3, [r7, #12]
	ldr	r3, [r7, #4]
	cmp	r3, #0
	bne	.NEXT
	movs	r3, #0
	b	.FINISH
.NEXT:
	ldr	r3, [r7, #4]
	cmp	r3, #1
	bne	.STORE
	movs	r3, #1
	b	.FINISH

.STORE:
	movs	r3, #0
	str	r3, [r7, #8]
	b	.RECURE2

.RECURE:
	ldr	r2, [r7, #16]
	ldr	r3, [r7, #20]
	add	r3, r3, r2
	str	r3, [r7, #12]
	ldr	r3, [r7, #16]
	str	r3, [r7, #20]
	ldr	r3, [r7, #12]
	str	r3, [r7, #16]
	ldr	r3, [r7, #8]
	adds	r3, r3, #1
	str	r3, [r7, #8]

.RECURE2:
	ldr	r3, [r7, #4]
	subs	r2, r3, #2
	ldr	r3, [r7, #8]
	cmp	r2, r3
	bgt	.RECURE
	ldr	r3, [r7, #12]

.FINISH:
	mov	r0, r3
	adds	r7, r7, #28
	pop 	{r4-r7}
	bx	lr	