# 📂 프로젝트 디렉토리 구조 및 실행 가이드

## 📌 디렉토리 구조

```
📦 프로젝트 루트
├── 📂 cpp/                      # 실습용 작업 디렉토리
│   ├── 📂 skeleton/             # 뼈대 코드 디렉토리
│   ├── 📂 solution/             # 정답 코드 디렉토리
├── 📂 doc/                      # 실습 문서 디렉토리
│   ├── 📜 CG_Lab_02_User_Interactions.pdf       # 기초 실습 문서
│   ├── 📜 CG_Lab_02_User_Interactions_Adv.pdf   # 심화 이론/실습 문서
```

---

## ⚠️ 실행 주의사항

`solution/` 폴더의 정답 코드를 실행하려면, **현재 디렉토리의 `main.cpp`를 해당 코드로 덮어쓴 후 빌드 및 실행**해야 합니다.  
(*소스 코드가 `./shader/` 폴더 아래의 쉐이더 코드를 참조하도록 작성되었기 때문입니다.*)

### ✅ 실행 예제

```sh
$ cd ./cpp
$ cp ./solution/main.cpp ./main.cpp
$ make
$ ./interaction
```

---

🚀 **올바르게 빌드하고 실행하여 실습을 진행하세요!** 😊
