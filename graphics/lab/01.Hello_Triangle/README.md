# 📂 프로젝트 디렉토리 구조 및 실행 가이드

## 📌 디렉토리 구조

```
📦 프로젝트 루트
├── 📜 main.cpp                   # 실습용 코드
├── 📜 Makefile                   # Makefile
├── 📂 skeleton_codes/            # 연습 코드 디렉토리
├── 📂 complete_codes/            # 완성된 코드 디렉토리
│   ├── 📂 cpu_mem/               # CPU 메모리 기반 렌더링
│   │   ├── 📜 triangle_soup.cpp   # Triangle Soup 기반 렌더링 코드
│   │   ├── 📜 vlist_triangles.cpp # Vertex list & Triangles 기반 렌더링 코드
│   ├── 📂 gpu_mem/               # GPU 메모리 기반 렌더링
│   │   ├── 📜 triangle_soup.cpp   # VBO를 이용한 Triangle Soup 기반 렌더링 코드
│   │   ├── 📜 vlist_triangles.cpp # VBO와 IBO를 이용한 Vertex list & Triangles 기반 렌더링 코드
├── 📂 doc/                       # 실습 문서 디렉토리
│   ├── 📜 CG_Lab_01_Hello_Triangle.pdf       # 기초 실습 문서
│   ├── 📜 CG_Lab_01_Hello_Triangle_Adv.pdf   # 심화 이론/실습 문서
```

---

## ⚠️ 실행 주의사항

`complete_codes/` 폴더의 코드를 실행하려면, **현재 디렉토리의 `main.cpp`를 해당 코드로 덮어쓴 후 빌드 및 실행**해야 합니다.  
(*소스 코드가 `./shader/` 폴더 아래의 쉐이더 코드를 참조하도록 작성되었기 때문입니다.*)

### ✅ 실행 예제

```sh
# GPU 메모리를 이용한 VBO 기반 Triangle Soup 렌더링 코드
$ cp ./complete_codes/gpu_mem/triangle_soup.cpp ./main.cpp
$ make
$ ./triangle
```

---

🚀 **올바르게 빌드하고 실행하여 실습을 진행하세요!** 😊