
astall：     文件格式 elf64-x86-64


Disassembly of section .init:

0000000000400658 <_init>:
_init():
  400658:	sub    $0x8,%rsp
  40065c:	mov    0x200995(%rip),%rax        # 600ff8 <_DYNAMIC+0x1e0>
  400663:	test   %rax,%rax
  400666:	je     40066d <_init+0x15>
  400668:	callq  400710 <pthread_mutex_lock@plt+0x10>
  40066d:	add    $0x8,%rsp
  400671:	retq   

Disassembly of section .plt:

0000000000400680 <pthread_create@plt-0x10>:
  400680:	pushq  0x200982(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400686:	jmpq   *0x200984(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40068c:	nopl   0x0(%rax)

0000000000400690 <pthread_create@plt>:
  400690:	jmpq   *0x200982(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400696:	pushq  $0x0
  40069b:	jmpq   400680 <_init+0x28>

00000000004006a0 <__stack_chk_fail@plt>:
  4006a0:	jmpq   *0x20097a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  4006a6:	pushq  $0x1
  4006ab:	jmpq   400680 <_init+0x28>

00000000004006b0 <__libc_start_main@plt>:
  4006b0:	jmpq   *0x200972(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  4006b6:	pushq  $0x2
  4006bb:	jmpq   400680 <_init+0x28>

00000000004006c0 <pthread_mutex_unlock@plt>:
  4006c0:	jmpq   *0x20096a(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  4006c6:	pushq  $0x3
  4006cb:	jmpq   400680 <_init+0x28>

00000000004006d0 <__printf_chk@plt>:
  4006d0:	jmpq   *0x200962(%rip)        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  4006d6:	pushq  $0x4
  4006db:	jmpq   400680 <_init+0x28>

00000000004006e0 <pthread_join@plt>:
  4006e0:	jmpq   *0x20095a(%rip)        # 601040 <_GLOBAL_OFFSET_TABLE_+0x40>
  4006e6:	pushq  $0x5
  4006eb:	jmpq   400680 <_init+0x28>

00000000004006f0 <sleep@plt>:
  4006f0:	jmpq   *0x200952(%rip)        # 601048 <_GLOBAL_OFFSET_TABLE_+0x48>
  4006f6:	pushq  $0x6
  4006fb:	jmpq   400680 <_init+0x28>

0000000000400700 <pthread_mutex_lock@plt>:
  400700:	jmpq   *0x20094a(%rip)        # 601050 <_GLOBAL_OFFSET_TABLE_+0x50>
  400706:	pushq  $0x7
  40070b:	jmpq   400680 <_init+0x28>

Disassembly of section .plt.got:

0000000000400710 <.plt.got>:
  400710:	jmpq   *0x2008e2(%rip)        # 600ff8 <_DYNAMIC+0x1e0>
  400716:	xchg   %ax,%ax

Disassembly of section .text:

0000000000400720 <main>:
main():
/work/linux-sys/DEBUG/astall/astall.c:41
        sleep(1);
    }
}

int main(int argc, char * argv[])
{
  400720:	sub    $0x18,%rsp
/work/linux-sys/DEBUG/astall/astall.c:45

    pthread_t tid;
    
    pthread_create(&tid, NULL, thr , NULL);
  400724:	xor    %ecx,%ecx
  400726:	mov    $0x400870,%edx
  40072b:	xor    %esi,%esi
  40072d:	mov    %rsp,%rdi
/work/linux-sys/DEBUG/astall/astall.c:41
        sleep(1);
    }
}

int main(int argc, char * argv[])
{
  400730:	mov    %fs:0x28,%rax
  400739:	mov    %rax,0x8(%rsp)
  40073e:	xor    %eax,%eax
/work/linux-sys/DEBUG/astall/astall.c:45

    pthread_t tid;
    
    pthread_create(&tid, NULL, thr , NULL);
  400740:	callq  400690 <pthread_create@plt>
/work/linux-sys/DEBUG/astall/astall.c:46
    pthread_join(tid, NULL);
  400745:	mov    (%rsp),%rdi
  400749:	xor    %esi,%esi
  40074b:	callq  4006e0 <pthread_join@plt>
/work/linux-sys/DEBUG/astall/astall.c:49
    return EXIT_SUCCESS;

}
  400750:	mov    0x8(%rsp),%rdx
  400755:	xor    %fs:0x28,%rdx
  40075e:	jne    400767 <main+0x47>
  400760:	xor    %eax,%eax
  400762:	add    $0x18,%rsp
  400766:	retq   
  400767:	callq  4006a0 <__stack_chk_fail@plt>
  40076c:	nopl   0x0(%rax)

0000000000400770 <_start>:
_start():
  400770:	xor    %ebp,%ebp
  400772:	mov    %rdx,%r9
  400775:	pop    %rsi
  400776:	mov    %rsp,%rdx
  400779:	and    $0xfffffffffffffff0,%rsp
  40077d:	push   %rax
  40077e:	push   %rsp
  40077f:	mov    $0x400990,%r8
  400786:	mov    $0x400920,%rcx
  40078d:	mov    $0x400720,%rdi
  400794:	callq  4006b0 <__libc_start_main@plt>
  400799:	hlt    
  40079a:	nopw   0x0(%rax,%rax,1)

00000000004007a0 <deregister_tm_clones>:
deregister_tm_clones():
  4007a0:	mov    $0x60106f,%eax
  4007a5:	push   %rbp
  4007a6:	sub    $0x601068,%rax
  4007ac:	cmp    $0xe,%rax
  4007b0:	mov    %rsp,%rbp
  4007b3:	jbe    4007d0 <deregister_tm_clones+0x30>
  4007b5:	mov    $0x0,%eax
  4007ba:	test   %rax,%rax
  4007bd:	je     4007d0 <deregister_tm_clones+0x30>
  4007bf:	pop    %rbp
  4007c0:	mov    $0x601068,%edi
  4007c5:	jmpq   *%rax
  4007c7:	nopw   0x0(%rax,%rax,1)
  4007d0:	pop    %rbp
  4007d1:	retq   
  4007d2:	nopl   0x0(%rax)
  4007d6:	nopw   %cs:0x0(%rax,%rax,1)

00000000004007e0 <register_tm_clones>:
register_tm_clones():
  4007e0:	mov    $0x601068,%esi
  4007e5:	push   %rbp
  4007e6:	sub    $0x601068,%rsi
  4007ed:	sar    $0x3,%rsi
  4007f1:	mov    %rsp,%rbp
  4007f4:	mov    %rsi,%rax
  4007f7:	shr    $0x3f,%rax
  4007fb:	add    %rax,%rsi
  4007fe:	sar    %rsi
  400801:	je     400818 <register_tm_clones+0x38>
  400803:	mov    $0x0,%eax
  400808:	test   %rax,%rax
  40080b:	je     400818 <register_tm_clones+0x38>
  40080d:	pop    %rbp
  40080e:	mov    $0x601068,%edi
  400813:	jmpq   *%rax
  400815:	nopl   (%rax)
  400818:	pop    %rbp
  400819:	retq   
  40081a:	nopw   0x0(%rax,%rax,1)

0000000000400820 <__do_global_dtors_aux>:
__do_global_dtors_aux():
  400820:	cmpb   $0x0,0x200859(%rip)        # 601080 <completed.7594>
  400827:	jne    40083a <__do_global_dtors_aux+0x1a>
  400829:	push   %rbp
  40082a:	mov    %rsp,%rbp
  40082d:	callq  4007a0 <deregister_tm_clones>
  400832:	pop    %rbp
  400833:	movb   $0x1,0x200846(%rip)        # 601080 <completed.7594>
  40083a:	repz retq 
  40083c:	nopl   0x0(%rax)

0000000000400840 <frame_dummy>:
frame_dummy():
  400840:	mov    $0x600e10,%edi
  400845:	cmpq   $0x0,(%rdi)
  400849:	jne    400850 <frame_dummy+0x10>
  40084b:	jmp    4007e0 <register_tm_clones>
  40084d:	nopl   (%rax)
  400850:	mov    $0x0,%eax
  400855:	test   %rax,%rax
  400858:	je     40084b <frame_dummy+0xb>
  40085a:	push   %rbp
  40085b:	mov    %rsp,%rbp
  40085e:	callq  *%rax
  400860:	pop    %rbp
  400861:	jmpq   4007e0 <register_tm_clones>
  400866:	nopw   %cs:0x0(%rax,%rax,1)

0000000000400870 <thr>:
thr():
/work/linux-sys/DEBUG/astall/astall.c:21
    cnt = 0;
    pthread_mutex_unlock(&mutex);
}

void *thr(void *arg)
{
  400870:	sub    $0x8,%rsp
  400874:	jmp    4008b4 <thr+0x44>
  400876:	nopw   %cs:0x0(%rax,%rax,1)
/work/linux-sys/DEBUG/astall/astall.c:31
        {
            cnt_reset();
        }
        else
        {
            cnt ++;
  400880:	add    $0x1,%eax
  400883:	mov    %eax,0x200817(%rip)        # 6010a0 <cnt>
/work/linux-sys/DEBUG/astall/astall.c:33
        }
        pthread_mutex_unlock(&mutex);
  400889:	mov    $0x6010c0,%edi
  40088e:	callq  4006c0 <pthread_mutex_unlock@plt>
printf():
/usr/include/x86_64-linux-gnu/bits/stdio2.h:104
}

__fortify_function int
printf (const char *__restrict __fmt, ...)
{
  return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
  400893:	mov    0x200807(%rip),%edx        # 6010a0 <cnt>
  400899:	mov    $0x1,%edi
  40089e:	mov    $0x4009a4,%esi
  4008a3:	xor    %eax,%eax
  4008a5:	callq  4006d0 <__printf_chk@plt>
thr():
/work/linux-sys/DEBUG/astall/astall.c:36

        printf("%d\n\n", cnt);
        sleep(1);
  4008aa:	mov    $0x1,%edi
  4008af:	callq  4006f0 <sleep@plt>
/work/linux-sys/DEBUG/astall/astall.c:24

void *thr(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
  4008b4:	mov    $0x6010c0,%edi
  4008b9:	callq  400700 <pthread_mutex_lock@plt>
/work/linux-sys/DEBUG/astall/astall.c:25
        if(cnt > 2)
  4008be:	mov    0x2007dc(%rip),%eax        # 6010a0 <cnt>
  4008c4:	cmp    $0x2,%eax
  4008c7:	jle    400880 <thr+0x10>
cnt_reset():
/work/linux-sys/DEBUG/astall/astall.c:15

int cnt = 0;

void cnt_reset(void)
{
    pthread_mutex_lock(&mutex);
  4008c9:	mov    $0x6010c0,%edi
  4008ce:	callq  400700 <pthread_mutex_lock@plt>
/work/linux-sys/DEBUG/astall/astall.c:17
    cnt = 0;
    pthread_mutex_unlock(&mutex);
  4008d3:	mov    $0x6010c0,%edi
/work/linux-sys/DEBUG/astall/astall.c:16
int cnt = 0;

void cnt_reset(void)
{
    pthread_mutex_lock(&mutex);
    cnt = 0;
  4008d8:	movl   $0x0,0x2007be(%rip)        # 6010a0 <cnt>
/work/linux-sys/DEBUG/astall/astall.c:17
    pthread_mutex_unlock(&mutex);
  4008e2:	callq  4006c0 <pthread_mutex_unlock@plt>
  4008e7:	jmp    400889 <thr+0x19>
thr():
  4008e9:	nopl   0x0(%rax)

00000000004008f0 <cnt_reset>:
cnt_reset():
/work/linux-sys/DEBUG/astall/astall.c:14
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int cnt = 0;

void cnt_reset(void)
{
  4008f0:	sub    $0x8,%rsp
/work/linux-sys/DEBUG/astall/astall.c:15
    pthread_mutex_lock(&mutex);
  4008f4:	mov    $0x6010c0,%edi
  4008f9:	callq  400700 <pthread_mutex_lock@plt>
/work/linux-sys/DEBUG/astall/astall.c:16
    cnt = 0;
  4008fe:	movl   $0x0,0x200798(%rip)        # 6010a0 <cnt>
/work/linux-sys/DEBUG/astall/astall.c:17
    pthread_mutex_unlock(&mutex);
  400908:	mov    $0x6010c0,%edi
/work/linux-sys/DEBUG/astall/astall.c:18
}
  40090d:	add    $0x8,%rsp
/work/linux-sys/DEBUG/astall/astall.c:17

void cnt_reset(void)
{
    pthread_mutex_lock(&mutex);
    cnt = 0;
    pthread_mutex_unlock(&mutex);
  400911:	jmpq   4006c0 <pthread_mutex_unlock@plt>
  400916:	nopw   %cs:0x0(%rax,%rax,1)

0000000000400920 <__libc_csu_init>:
__libc_csu_init():
  400920:	push   %r15
  400922:	push   %r14
  400924:	mov    %edi,%r15d
  400927:	push   %r13
  400929:	push   %r12
  40092b:	lea    0x2004ce(%rip),%r12        # 600e00 <__frame_dummy_init_array_entry>
  400932:	push   %rbp
  400933:	lea    0x2004ce(%rip),%rbp        # 600e08 <__init_array_end>
  40093a:	push   %rbx
  40093b:	mov    %rsi,%r14
  40093e:	mov    %rdx,%r13
  400941:	sub    %r12,%rbp
  400944:	sub    $0x8,%rsp
  400948:	sar    $0x3,%rbp
  40094c:	callq  400658 <_init>
  400951:	test   %rbp,%rbp
  400954:	je     400976 <__libc_csu_init+0x56>
  400956:	xor    %ebx,%ebx
  400958:	nopl   0x0(%rax,%rax,1)
  400960:	mov    %r13,%rdx
  400963:	mov    %r14,%rsi
  400966:	mov    %r15d,%edi
  400969:	callq  *(%r12,%rbx,8)
  40096d:	add    $0x1,%rbx
  400971:	cmp    %rbp,%rbx
  400974:	jne    400960 <__libc_csu_init+0x40>
  400976:	add    $0x8,%rsp
  40097a:	pop    %rbx
  40097b:	pop    %rbp
  40097c:	pop    %r12
  40097e:	pop    %r13
  400980:	pop    %r14
  400982:	pop    %r15
  400984:	retq   
  400985:	nop
  400986:	nopw   %cs:0x0(%rax,%rax,1)

0000000000400990 <__libc_csu_fini>:
__libc_csu_fini():
  400990:	repz retq 

Disassembly of section .fini:

0000000000400994 <_fini>:
_fini():
  400994:	sub    $0x8,%rsp
  400998:	add    $0x8,%rsp
  40099c:	retq   
