	.text
	.syntax unified
	.thumb
	.global	listsum_recursive_asm	
	.type listsum_recursive_asm, %function
listsum_recursive_asm:
/*
	Your implementation goes here. 
*/
	push 	{r4, r7, lr}
	sub	sp, sp, #12
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, [r7, #4]
	ldr	r3, [r3, #4]
	cmp 	r3, #0
	bne	RECURE1
	ldr	r3, [r7, #4]
	ldr	r3, [r3]
	b	FINISH


RECURE1:	
	ldr	r3, [r7, #4]
	ldr	r4, [r3]
	ldr	r3, [r7, #4]
	ldr	r3, [r3, #4]
	mov	r0, r3
	bl	listsum_recursive_asm
	mov	r3, r0
	add	r3, r4, r3


FINISH:	
	mov	r0, r3
	mov	sp, r7
	add	sp, sp, #12
	pop 	{r4, r7, pc }	
	bx	lr
