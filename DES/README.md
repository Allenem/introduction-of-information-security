# DES算法的c语言实现

## 功能如下

- [x] 字符串加密——请输入1
- [x] 字符串解密——请输入2
- [x] 文件加密——请输入3
- [x] 文件解密——请输入4
- [x] 退出——请输入其他任意键

## DES算法说明

### 1.整个过程

```
+----------------------------------------------------------------------+
|                                           
|                          64位输入                  
|                                                    
|                             ↓                      
|                                           
|                        初始变换(IP)
|
|                      ↓             ↓ 
|                     
|                 L0(32bit)          R0(32bit) 
|
|                      ↓             ↓ 
|                     
|           L1(32bit)=R0(32bit)   R1(32bit)=L0⊕f(R0,k1)
|
|                      ↓             ↓ 
|                     
|           L2(32bit)=R1(32bit)   R2(32bit)=L1⊕f(R1,k2)
|
|                      ↓             ↓ 
|                     
|                      ……             ……
|
|                      ↓             ↓ 
|                     
|      Li(32bit)=R(i-1)(32bit)    Ri(32bit)=L(i-1)⊕f(R(i-1),ki)
|
|                      ↓             ↓ 
|                     
|                      ……             ……
|
|                      ↓             ↓ 
|                     
|          L16(32bit)=R15(32bit) R16(32bit)=L15⊕f(R15,k16)
|
|                      ↓             ↓ 
|                     
|                     逆初始变换(IP^(-1))
|                                           
|                             ↓                      
|                                           
|                          64位输出
+----------------------------------------------------------------------+
```

### 2.f函数

```
+----------------------------------------------------------------------+
|                                           
|                                           
|     L(i-1)                R(i-1)                 key(48bit)
|                                                      
|      |  ┌------------------ ↓                        |
|      |  |                                            |
|      |  |        拓展置换(32bit->48bit)               |
|      |  |                                            |
|      |  |                   ↓                        |
|      |  |                                            |
|      |  |                   ⊕ ←---------------------┘
|      |  |     
|      |  |                   ↓ 
|      |  |             
|      |  |            s-盒(48bit->32bit) 
|      |  |
|      |  |                   ↓ 
|      |  |             
|      |  |                 p-盒
|      |  |
|      |  |                   ↓ 
|      |  |             
|      ┕--------------------→ ⊕
|         | 
|         ↓                   ↓ 
|                     
|         Li                  Ri
|                                           
|                     
+----------------------------------------------------------------------+
```

### 3.子密钥产生过程

```
+----------------------------------------------------------------------+
|                                           
|                                           
|             K(64bit)   
|                                                      
|                ↓            
|  
|      置换选择1(64bit->56bit)    
|                              
|         ↓                ↓     
|   
|        C0       +       D0
|                              
|         ↓                ↓     
|   
|        LS               LS
|                              
|         ↓                ↓     
|   
|        C1       +       D1 -→ 置换选择2(56bit->48bit) -→ k1(48bit)  
|                              
|         ↓                ↓     
|   
|        LS               LS
|                              
|         ↓                ↓     
|                              
|        ……               ……     
|                              
|         ↓                ↓     
|   
|        LS               LS
|                              
|         ↓                ↓     
|   
|        C16      +      D16 -→ 置换选择2(56bit->48bit) -→ k16(48bit)  
|                     
+----------------------------------------------------------------------+
```

## 编程说明

看代码吧(*/ω＼*)，暂时太懒了... 我一定补回来。

## 运行截图

![EDS](img/EDS.png)

![txt](img/txt.png)