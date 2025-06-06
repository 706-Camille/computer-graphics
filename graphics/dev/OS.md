# 🛠️ 운영 체제

## 🌍 공식 운영체제

컴퓨터그래픽스 교과목의 **공식 운영체제**는 `Ubuntu LTS 18.04+ (18.04, 20.04, 22.04, 24.04 등)`입니다. 
> ⚠️ **주의:** Windows, Mac, 기타 Linux 배포판은 **비공식 운영체제**이며, 본 교과목은 **비공식 운영체제에 대해서 기술 지원을 제공하지 않습니다.**  

---

## 🌍 비공식 운영체제

부득이하게 비공식 운영체제인 Windows나 Mac을 사용하는 학생들의 개발 편의를 위해 제공되는 정보입니다. 반드시 ⚠️ 주의 사항을 읽어보세요.

> ⚠️ **주의:** 과제 및 프로젝트의 최종 평가는 공식 운영체제(Ubuntu LTS 18.04+)에서 빌드 및 실행된 결과물을 기준으로 진행됩니다. 


### 💡 **가상 환경 (추천 방식)**  

비공식 운영체제에서 **Ubuntu LTS 18.04+**를 사용하는 가장 쉬운 방법은 **가상 머신(VM)**을 이용하는 것입니다.  

- [VMWare](https://www.vmware.com/) 또는 [VirtualBox](https://www.virtualbox.org/)를 이용해 Ubuntu를 설치  
- 현재 사용 중인 운영체제(**Host OS**) 위에 **Ubuntu LTS 18.04+ (**Guest OS**)를 실행  
- 과제 수행을 위한 **가장 간단하고 안정적인 방법**  

---

### 💻 Windows에서 Ubuntu 유사 개발 환경 구축하기

Windows에서 Ubuntu 유사 개발 환경을 다음의 두가지 방법 중 하나로 구축할 수 있습니다.
 1) MSYS2 + MinGW 개발 환경 구축
 2) WSL2 이용하기


#### 1. **MSYS2 + MinGW** 개발 환경 구축
**MSYS2 + MinGW**를 설치하면, Linux와 유사한 개발 환경을 Windows에서 구축할 수 있습니다. 이 방식은 다음의 특징이 있습니다.
- 작성한 소스 코드를 빌드하면 Windows 바이너리인 `*.exe` 파일이 나옴
- 작성한 소스 코드는 특별한 수정없이 Ubunutu 환경에서 빌드할 수 있음
- [설치 및 사용법](https://github.com/kmuvcl/graphics/blob/main/dev/mingw.md) 참고  

#### 2. **WSL2 (Windows Subsystem for Linux)** 이용하기
Windows의 내부시스템(subsystem)으로 Linux 배포판을 설치하여 Windows에서 개발 환경을 구축할 수 있습니다.

**설치 방법:**  
- Microsoft Store에서 **Ubuntu LTS 최신 배포판** 설치  
- [WSL2 설치 가이드](https://learn.microsoft.com/en-us/windows/wsl/install) 참고  
- OpenGL 프로그램을 실행하려면 [VcXsrv Windows X Server](https://sourceforge.net/projects/vcxsrv/) 설치  

---

## 📢 추가 안내  
- 과제 및 실습 환경 구축이 어려운 경우, **조교 또는 동료들과 소통하며 해결**하는 것을 추천합니다.  
- 공식 운영체제(Ubuntu LTS 18.04+)에서의 개발을 우선으로 고려하세요.  

🚀 **원활한 개발 환경 구축을 바랍니다!** 😊  
