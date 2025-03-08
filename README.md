# Randomart

Randomart implementation using Symbolic Regression in C 

*Heavily inspired (but not based of!) by ![Tsoding's randomart implementation](https://github.com/tsoding/randomart/tree/main).*

![image](https://github.com/user-attachments/assets/49a2cb30-2038-4629-8038-e10dd43eee96)


Above image were produced by following expressions:

Red channel
```
((ln(x) mod sqrt(y)) + ln(y))
```

Green channel
```
(sin(ln(ln(((cos((x * 0.905806)) * tan(sqrt(sin((((ln(cos((ln(0.431774) * 0.751206))) - sqrt(cos(ln(y)))) / ln(cos(((y * (tan(0.518991) - sqrt((tan(cos(ln(y))) * (y + y))))) - (y / x))))) + (cos(tan((((x + 0.840772) + sqrt(x)) / sin((ln(ln(y)) mod sqrt(ln(sin(sin(cos(ln((0.294030 + (((sqrt(x) - cos(x)) * x) - (y / 0.861435)))))))))))))) + sqrt(x))))))) / x)))) mod y)
```

Blue channel
```
tan(((cos(ln(0.476469)) mod ln(sqrt(x))) - (ln(x) + 0.555270)))
```


## Quick Start

### Generate an image

```console
$ make
$ ./a.out > image.ppm
$ feh image.ppm
```

### Result:
![image](https://github.com/user-attachments/assets/a438f2e3-951d-4fd4-9063-94ffc66f5aab)
![image](https://github.com/user-attachments/assets/42d4fe01-9c33-4d1e-8345-e43068baf7d4)
![image](https://github.com/user-attachments/assets/4dd5a784-7e09-4a78-b44c-7dfc1638eb3e)
![image](https://github.com/user-attachments/assets/2674e925-b140-4244-897c-57d70c768a8d)
![image](https://github.com/user-attachments/assets/89951475-19ec-4412-95be-81fe67fa580d)
![image](https://github.com/user-attachments/assets/24352aa1-6596-4891-9298-f58c95fe05a4)
![image](https://github.com/user-attachments/assets/8580eb24-dc20-4c5a-a701-e5c0f37c3198)
![image](https://github.com/user-attachments/assets/87d8f525-a459-4a22-8803-047818af324f)
![image](https://github.com/user-attachments/assets/96f22a17-56f0-4b01-a59d-188dddd3f4c8)
![image](https://github.com/user-attachments/assets/8b43617d-6058-4390-9b1a-38b1bd292432)



