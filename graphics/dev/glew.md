# 📦 OpenGL Extension Wrangler Library (GLEW)


[**OpenGL Extension Wrangler Library (GLEW)**](https://glew.sourceforge.net/)은 **OpenGL 확장 기능을 손쉽게 쓸 수 있는 라이브러리**입니다. OpenGL에서는 기기에 설치된 GPU 별로 특화된 확장 기능을 쓸 수 있는 방식을 지원하는데, 이러한 OpenGL의 확장 기능을 손쉽게 사용하려면 아래 명령을 실행하여 **`libglew-dev`와 `glew-utils` 패키지를 설치**하면 됩니다.

---

## 🖥️ Ubuntu에서 설치하기  

Ubuntu 환경에서는 다음 명령어를 실행하여 `libglew-dev`와 `glew-utils` 패키지를 설치할 수 있습니다:

```bash
sudo apt install libglew-dev glew-utils 
```

설치가 완료되면 `pkg-config`를 이용하여 GLM 라이브러리가 정상적으로 설치되었는지 확인할 수 있습니다:

```bash
pkg-config --modversion glew
```

위 명령어를 실행했을 때 **버전 정보(예: 2.2.0)**가 출력되면 설치가 정상적으로 완료된 것입니다. 🚀

---

✅ **이제 GLEW를 활용하여 프로젝트를 빌드할 준비가 되었습니다!**

