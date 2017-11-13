	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	push {r4-r7}
	movs r1, #0
	cmp r0, #0
	bge Exit
	subs r0,r1,r0
Exit:	
	pop {r4-r7}	
	bx	lr
