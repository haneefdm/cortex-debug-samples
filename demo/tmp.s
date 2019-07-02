10080edc <main>:
10080edc:	b480      	push	{r7}
10080ede:	b083      	sub	sp, #12
10080ee0:	af00      	add	r7, sp, #0
10080ee2:	2300      	movs	r3, #0
10080ee4:	603b      	str	r3, [r7, #0]
10080ee6:	2300      	movs	r3, #0
10080ee8:	607b      	str	r3, [r7, #4]
10080eea:	232a      	movs	r3, #42	; 0x2a
10080eec:	603b      	str	r3, [r7, #0]
10080eee:	683a      	ldr	r2, [r7, #0]
10080ef0:	4b07      	ldr	r3, [pc, #28]	; (10080f10 <main+0x34>)
10080ef2:	681b      	ldr	r3, [r3, #0]
10080ef4:	441a      	add	r2, r3
10080ef6:	683b      	ldr	r3, [r7, #0]
10080ef8:	4053      	eors	r3, r2
10080efa:	603b      	str	r3, [r7, #0]
10080efc:	687b      	ldr	r3, [r7, #4]
10080efe:	3301      	adds	r3, #1
10080f00:	607b      	str	r3, [r7, #4]
10080f02:	4b03      	ldr	r3, [pc, #12]	; (10080f10 <main+0x34>)
10080f04:	681b      	ldr	r3, [r3, #0]
10080f06:	3301      	adds	r3, #1
10080f08:	4a01      	ldr	r2, [pc, #4]	; (10080f10 <main+0x34>)
10080f0a:	6013      	str	r3, [r2, #0]
10080f0c:	e7ef      	b.n	10080eee <main+0x12>
10080f0e:	bf00      	nop
10080f10:	080242a8 	.word	0x080242a8

10080f14 <memset>:
10080f14:	4402      	add	r2, r0
10080f16:	4603      	mov	r3, r0
10080f18:	4293      	cmp	r3, r2
10080f1a:	d100      	bne.n	10080f1e <memset+0xa>
10080f1c:	4770      	bx	lr
10080f1e:	f803 1b01 	strb.w	r1, [r3], #1
10080f22:	e7f9      	b.n	10080f18 <memset+0x4>

080242b4 <Cy_Flash_RAMDelay>:
 80242b4:	00c1b280 	.word	0x00c1b280
 80242b8:	b350      	cbz	r0, 8024310 <Cy_Flash_RAMDelay+0x5c>
 80242ba:	4b16      	.short	0x4b16
 80242bc:	681b      	ldr	r3, [r3, #0]
 80242be:	6a1a      	.short	0x6a1a
 80242c0:	f8b3 30b0 	ldrh.w	r3, [r3, #176]	; 0xb0
 80242c4:	03c3ebc3 	.word	0x03c3ebc3
 80242c8:	58d3      	ldr	r3, [r2, r3]
 80242ca:	2b00      	.short	0x2b00
 80242cc:	daf5      	bge.n	80242ba <Cy_Flash_RAMDelay+0x6>
 80242ce:	4b12      	.short	0x4b12
 80242d0:	223e      	movs	r2, #62	; 0x3e
 80242d2:	601a      	.short	0x601a
 80242d4:	3304      	adds	r3, #4
 80242d6:	f641      	.short	0xf641
 80242d8:	721e      	strb	r6, [r3, #8]
 80242da:	601a      	.short	0x601a
 80242dc:	f5a3 7384 	sub.w	r3, r3, #264	; 0x108
 80242e0:	f8c32206 	.word	0xf8c32206
 80242e4:	2518      	movs	r5, #24
 80242e6:	f021      	.short	0xf021
 80242e8:	417f      	adcs	r7, r7
 80242ea:	f8c3      	.short	0xf8c3
 80242ec:	151c      	asrs	r4, r3, #20
 80242ee:	f8d3 351c 	ldr.w	r3, [r3, #1308]	; 0x51c
 80242f2:	4b08      	ldr	r3, [pc, #32]	; (8024314 <Cy_Flash_RAMDelay+0x60>)
 80242f4:	681b      	ldr	r3, [r3, #0]
 80242f6:	6a1a      	ldr	r2, [r3, #32]
 80242f8:	f8b3 30b0 	ldrh.w	r3, [r3, #176]	; 0xb0
 80242fc:	ebc3 03c3 	rsb	r3, r3, r3, lsl #3
 8024300:	4413      	add	r3, r2
 8024302:	2200      	movs	r2, #0
 8024304:	605a      	str	r2, [r3, #4]
 8024306:	4b05      	ldr	r3, [pc, #20]	; (802431c <Cy_Flash_RAMDelay+0x68>)
 8024308:	f8d3 351c 	ldr.w	r3, [r3, #1308]	; 0x51c
 802430c:	2b00      	cmp	r3, #0
 802430e:	dafa      	bge.n	8024306 <Cy_Flash_RAMDelay+0x52>
 8024310:	4770      	bx	lr
 8024312:	bf00      	nop
 8024314:	08024850 	.word	0x08024850
 8024318:	40260104 	.word	0x40260104
 802431c:	40260000 	.word	0x40260000
