/*-*- mode:unix-assembly; indent-tabs-mode:t; tab-width:8; coding:utf-8     -*-│
│vi: set et ft=asm ts=8 sw=8 fenc=utf-8                                     :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ This program is free software; you can redistribute it and/or modify         │
│ it under the terms of the GNU General Public License as published by         │
│ the Free Software Foundation; version 2 of the License.                      │
│                                                                              │
│ This program is distributed in the hope that it will be useful, but          │
│ WITHOUT ANY WARRANTY; without even the implied warranty of                   │
│ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU             │
│ General Public License for more details.                                     │
│                                                                              │
│ You should have received a copy of the GNU General Public License            │
│ along with this program; if not, write to the Free Software                  │
│ Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA                │
│ 02110-1301 USA                                                               │
╚──────────────────────────────────────────────────────────────────────────────╝
	@fileoverview Cosmopolitan Memory Setter
	
	This sets one bit per picosecond on a $900 Skylake workstation,
	which is about 110 GBps. */
#include "libc/nexgen32e/x86feature.h"
#include "libc/nexgen32e/macros.h"
#include "libc/macros.h"
.source	__FILE__

/	Sets memory.
/
/	@param	rdi is dest
/	@param	esi is the byte to set
/	@param	edx is the number of bytes to set
/	@return	original rdi copied to rax
/	@mode	long
/	@asyncsignalsafe
memset:	mov	%rdi,%rax
/	fallthrough

/	Sets memory w/ minimal-impact ABI.
/
/	@param	rdi is dest
/	@param	esi is the byte to set
/	@param	edx is the number of bytes to set
/	@clob	flags,xmm3
/	@mode	long
_memset:.leafprologue
	.profilable
	push	%rbx
	push	%rcx
	movd	%esi,%xmm3
	mov	$.Lmemsettab.ro.size,%ecx
	cmp	%rcx,%rdx
	cmovb	%rdx,%rcx
	ezlea	memsettab,bx
	jmp	*(%rbx,%rcx,8)
.Lanchorpoint:
.L32r:	cmp	$1024,%rdx
	jae	.Lerms
.L32:	vpbroadcastb %xmm3,%ymm3
	mov	$32,%ecx
1:	lea	32(%rcx),%rcx
	vmovdqu	%ymm3,-64(%rdi,%rcx)
	cmp	%rcx,%rdx
	ja	1b
	vmovdqu	%ymm3,-32(%rdi,%rdx)
	vxorps	%ymm3,%ymm3,%ymm3
	jmp	.L0
.L16r:	cmp	$1024,%rdx
	jae	.Lerms
.L16:	pbroadcastb %xmm3
	mov	$16,%ecx
1:	lea	16(%rcx),%rcx
	movdqu	%xmm3,-32(%rdi,%rcx)
	cmp	%rcx,%rdx
	ja	1b
	movdqu	%xmm3,-16(%rdi,%rdx)
	xorps	%xmm3,%xmm3
.L0:	pop	%rcx
	pop	%rbx
	.leafepilogue
.L8:	movzbq	%sil,%rbx
	mov	$0x0101010101010101,%rcx
	imul	%rcx,%rbx
	mov	%rbx,(%rdi)
	mov	%rbx,-8(%rdi,%rdx)
	jmp	.L0
.L4:	movzbl	%sil,%ebx
	mov	$0x01010101,%ecx
	imul	%ecx,%ebx
	mov	%ebx,(%rdi)
	mov	%ebx,-4(%rdi,%rdx)
	jmp	.L0
.L3:	mov	%sil,2(%rdi)
.L2:	mov	%sil,1(%rdi)
.L1:	mov	%sil,(%rdi)
	jmp	.L0
.Lerms:	push	%rax
	push	%rdi
	mov	%esi,%eax
	mov	%rdx,%rcx
	rep stosb
	pop	%rdi
	pop	%rax
	jmp	.L0
	.endfn	_memset,globl,hidden
	.endfn	memset,globl

	.initro 300,_init_memset
memsettab.ro:
	.byte	.L0 - .Lanchorpoint
	.byte	.L1 - .Lanchorpoint
	.byte	.L2 - .Lanchorpoint
	.byte	.L3 - .Lanchorpoint
	.rept	4
	.byte	.L4 - .Lanchorpoint
	.endr
	.rept	8
	.byte	.L8 - .Lanchorpoint
	.endr
	.rept	16
	.byte	.L16 - .Lanchorpoint
	.endr
	.equ	.Lmemsettab.ro.size,.-memsettab.ro
	.endobj	memsettab.ro
	.if	.Lmemsettab.ro.size % 8
	.error	"moar jmptab"
	.endif
	.byte	.L16 - .Lanchorpoint		# SSE2
	.byte	.L16r - .Lanchorpoint		# SSE2 + ERMS
	.byte	.L32 - .Lanchorpoint		# AVX2
	.byte	.L32r - .Lanchorpoint		# AVX2 + ERMS
	.byte	0,0,0,0
	.previous

	.initbss 300,_init_memset
memsettab:
	.rept	.Lmemsettab.ro.size
	.quad	0
	.endr
	.quad	0
	.endobj	memsettab
	.previous

	.init.start 300,_init_memset
	pushpop	.Lmemsettab.ro.size,%rcx
	ezlea	.Lanchorpoint,dx
	testb	X86_HAVE(AVX2)+kCpuids(%rip)
	call	memjmpinit
	.init.end 300,_init_memset

/*	benchmarks on intel core i7-6700 @ 3.40GHz (skylake)
	includes function call overhead (unless marked otherwise)

	Your memset() for #c per n where c ≈ 0.273ns
	N                     x1            x8           x64	mBps
	------------------------------------------------------------
	1                 73.000        35.125        36.141      97
	1                 35.000        36.375        35.984      97
	2                 28.500        19.938        18.820     185
	3                 19.000        12.458        12.651     276
	4                 15.750        10.719         9.566     365
	7                  5.000         5.411         5.730     609
	8                  8.375         4.953         4.697     743
	15                 4.200         2.408         2.407    1450
	16                 7.188         2.539         2.382    1465 «
	31                 1.129         1.206         1.183    2950
	32                15.156         2.012         1.292    2702
	63                 4.016         0.986         0.663    5264
	64                 3.547         0.967         0.684    5104
	127                2.087         0.562         0.338   10311
	128                1.805         0.499         0.336   10393
	255                0.412         0.180         0.183   19119
	256                0.160         0.170         0.169   20650
	511                0.162         0.134         0.108   32214
	512                0.100         0.106         0.104   33507
	1023               0.110         0.095         0.082   42574
	1024               0.099         0.080         0.078   44944
	2047               0.155         0.154         0.154   22624
	2048               0.052         0.052         0.053   66266
	4095               0.098         0.099         0.099   35142
	4096               0.042         0.042         0.041   84250
	8191               0.072         0.073         0.072   48157
	8192               0.034         0.034         0.034  101332
	16383              0.059         0.059         0.059   58997
	16384              0.031         0.031         0.031  112972
	32767              0.054         0.054         0.054   65053
	32768              0.029         0.029         0.029  119433
	65535              0.069         0.069         0.068   51690
	65536              0.057         0.057         0.057   61434
	131071             0.066         0.066         0.066   53001
	131072             0.057         0.058         0.057   60716
	262143             0.066         0.065         0.065   53462
	262144             0.060         0.058         0.058   60104
	524287             0.067         0.068         0.072   48784
	524288             0.063         0.062         0.061   56957
	1048575            0.068         0.068         0.069   50353
	1048576            0.062         0.060         0.062   56661
	2097151            0.066         0.066         0.067   52421
	2097152            0.060         0.060         0.061   57672
	4194303            0.072         0.067         0.067   51910
	4194304            0.062         0.061         0.062   56327
	8388607            0.129         0.111         0.111   31368
	8388608            0.136         0.119         0.111   31519

	glibc memset() for #c per n where c ≈ 0.273ns
	N                     x1            x8           x64	mBps
	------------------------------------------------------------
	1                121.000        39.125        35.547      98
	1                 33.000        35.875        35.172      99
	2                 17.500        18.312        18.070     193
	3                 16.333        14.542        12.411     281
	4                 12.250         9.344         9.215     379
	7                  7.571         5.732         5.453     640
	8                  4.625         4.641         4.623     755
	15                 4.467         3.158         2.478    1408
	16                 2.312         2.289         2.468    1414
	31                 2.290         1.367         1.278    2731
	32                 1.219         1.176         1.182    2952
	63                 0.905         0.696         0.656    5320
	64                 0.672         0.658         0.660    5285
	127                1.299         0.723         0.673    5183
	128                0.508         0.423         0.424    8227
	255                0.490         0.428         0.417    8367
	256                0.293         0.233         0.243   14349
	511                0.284         0.232         0.234   14902
	512                0.154         0.131         0.131   26626
	1023               0.155         0.137         0.135   25839
	1024               0.089         0.078         0.080   43875
	2047               0.103         0.092         0.090   38672
	2048               0.060         0.054         0.054   65116
	4095               0.073         0.068         0.068   51405
	4096               0.046         0.042         0.042   82162
	8191               0.060         0.058         0.057   60739
	8192               0.036         0.034         0.034  101467
	16383              0.052         0.052         0.051   68594
	16384              0.031         0.031         0.031  112603
	32767              0.053         0.050         0.049   70850
	32768              0.032         0.029         0.029  119617
	65535              0.067         0.067         0.067   52015
	65536              0.058         0.058         0.058   60440
	131071             0.067         0.066         0.065   53518
	131072             0.059         0.058         0.058   60281
	262143             0.066         0.065         0.065   54005
	262144             0.058         0.058         0.058   60121
	524287             0.067         0.067         0.067   52349
	524288             0.061         0.061         0.064   54699
	1048575            0.068         0.067         0.067   51876
	1048576            0.061         0.061         0.061   56775
	2097151            0.068         0.068         0.068   51379
	2097152            0.062         0.062         0.062   56513
	4194303            0.069         0.068         0.069   50580
	4194304            0.063         0.064         0.063   55751
	8388607            0.120         0.118         0.120   28998
	8388608            0.137         0.123         0.117   29936

	GCC (Inline REP STOSB) for #c per n where c ≈ 0.273ns
	N                     x1            x8           x64	mBps
	------------------------------------------------------------
	1                413.000       434.125       441.453       8
	1                431.000       436.125       438.953       8
	2                223.500       224.438       224.836      16
	3                149.000       150.042       623.786       6
	4                108.750       109.531       110.559      32
	7                 62.714        63.196        63.266      55
	8                 56.375        56.641        56.838      61
	15                30.467        30.708        30.761     113
	16                24.062        24.023        24.038     145
	31                14.548        14.859        14.876     235
	32                 9.719         9.691         9.730     359
	63                 7.286         7.312         7.339     476
	64                 3.609         3.705         3.721     938
	127                1.976         2.058         2.067    1689
	128                0.414         0.405         0.409    8532
	255                0.890         0.907         0.911    3832
	256                0.215         0.217         0.218   16039
	511                0.476         0.481         0.480    7273
	512                0.119         0.119         0.119   29270
	1023               0.257         0.260         0.260   13409
	1024               0.073         0.073         0.074   47442
	2047               0.150         0.150         0.151   23189
	2048               0.049         0.050         0.050   69424
	4095               0.096         0.097         0.097   36142
	4096               0.040         0.040         0.040   87842
	8191               0.071         0.071         0.071   49061
	8192               0.034         0.033         0.034  104099
	16383              0.058         0.059         0.058   59697
	16384              0.030         0.031         0.030  114585
	32767              0.053         0.053         0.053   66161
	32768              0.029         0.029         0.029  120750
	65535              0.069         0.069         0.069   50520
	65536              0.058         0.058         0.058   60100
	131071             0.068         0.067         0.085   40964
	131072             0.076         0.072         0.063   55514
	262143             0.067         0.093         0.090   38681
	262144             0.073         0.062         0.077   45384
	524287             0.107         0.093         0.066   52689
	524288             0.061         0.060         0.062   56294
	1048575            0.066         0.066         0.066   52990
	1048576            0.061         0.061         0.061   57248
	2097151            0.067         0.075         0.067   51887
	2097152            0.061         0.061         0.061   56878
	4194303            0.068         0.100         0.069   50623
	4194304            0.061         0.061         0.061   57195
	8388607            0.117         0.121         0.119   29441
	8388608            0.118         0.119         0.162   21587

	Musl memset() for #c per n where c ≈ 0.273ns
	N                     x1            x8           x64	mBps
	------------------------------------------------------------
	1                 49.000        35.625        35.172      99
	1                 33.000        34.625        35.109      99
	2                 17.500        17.562        18.023     194
	3                 20.333        14.042        12.411     281
	4                 11.250         9.219         9.301     375
	7                 11.857         6.018         5.417     644
	8                  4.125         4.516         4.592     760
	15                 4.200         2.692         2.480    1407
	16                 2.312         2.273         2.310    1511
	31                 2.097         1.786         1.342    2600
	32                 1.219         1.238         1.242    2811
	63                 0.841         0.815         0.686    5085
	64                 0.641         0.666         0.665    5246
	127                1.000         0.718         0.690    5061
	128                0.477         0.435         0.413    8451
	255                0.459         0.418         0.403    8670
	256                0.285         0.233         0.232   15051
	511                0.256         0.230         0.228   15285
	512                0.158         0.129         0.128   27170
	1023               0.134         0.140         0.138   25296
	1024               0.089         0.077         0.078   44891
	2047               0.094         0.088         0.088   39837
	2048               0.060         0.052         0.053   66075
	4095               0.071         0.068         0.068   51359
	4096               0.045         0.043         0.042   83178
	8191               0.059         0.058         0.057   60868
	8192               0.037         0.035         0.034  102662
	16383              0.052         0.051         0.051   68658
	16384              0.032         0.031         0.031  113568
	32767              0.050         0.049         0.049   71296
	32768              0.030         0.029         0.029  120029
	65535              0.067         0.067         0.068   50983
	65536              0.059         0.059         0.058   59665
	131071             0.067         0.067         0.067   52014
	131072             0.059         0.060         0.059   59211
	262143             0.067         0.066         0.066   52877
	262144             0.059         0.060         0.085   40900
	524287             0.067         0.066         0.065   53688
	524288             0.059         0.059         0.059   59112
	1048575            0.066         0.066         0.066   53181
	1048576            0.060         0.060         0.060   58300
	2097151            0.066         0.066         0.067   52439
	2097152            0.060         0.068         0.060   57924
	4194303            0.069         0.067         0.080   43425
	4194304            0.062         0.080         0.062   56085
	8388607            0.126         0.118         0.133   26207
	8388608            0.127         0.119         0.118   29643

	Newlib memset() for #c per n where c ≈ 0.273ns
	N                     x1            x8           x64	mBps
	------------------------------------------------------------
	1                443.000       440.875       440.078       8
	1                437.000       437.375       440.453       8
	2                226.500       226.438       227.461      15
	3                150.333       150.625       151.151      23
	4                113.250       113.281       113.770      31
	7                 66.714        67.232        66.998      52
	8                 58.375        58.828        58.811      59
	15                31.000        30.858        31.264     112
	16                31.438        28.523        28.317     123
	31                27.839        29.536        50.533      69
	32                11.281        10.918        11.068     315
	63                12.302        11.907        11.863     294
	64                 4.703         4.396         4.404     793
	127                2.732         2.719         2.712    1287
	128                0.852         0.729         0.736    4742
	255                1.188         1.178         1.171    2981
	256                0.652         0.416         0.381    9171
	511                1.474         1.629         1.662    2099
	512                0.287         0.264         0.246   14204
	1023               0.873         0.934         0.947    3684
	1024               0.196         0.179         0.178   19604
	2047               0.544         0.545         0.626    5572
	2048               0.257         0.257         0.253   13779
	4095               0.426         0.427         0.430    8110
	4096               0.282         0.296         0.293   11917
	8191               0.374         0.370         0.371    9402
	8192               0.297         0.310         0.400    8717
	16383              0.346         0.345         0.433    8062
	16384              0.313         0.312         0.311   11223
	32767              0.334         0.332         0.332   10505
	32768              0.313         0.313         0.358    9759
	65535              0.335         0.327         0.330   10589
	65536              0.330         0.312         0.337   10347
	131071             0.350         0.339         0.355    9825
	131072             0.334         0.329         0.359    9728
	262143             0.346         0.352         0.357    9785
	262144             0.350         0.375         0.482    7243
	524287             0.348         0.346         0.360    9691
	524288             0.347         0.346         0.385    9063
	1048575            0.358         0.375         0.383    9114
	1048576            0.355         0.382         0.388    8987
	2097151            0.362         0.368         0.390    8956
	2097152            0.363         0.375         0.387    9016
	4194303            0.361         0.379         0.385    9073
	4194304            0.366         0.376         0.385    9074
	8388607            0.363         0.366         0.372    9391
	8388608            0.419         0.374         0.370    9428 */
