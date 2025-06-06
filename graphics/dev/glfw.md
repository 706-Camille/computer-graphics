# 📦 Graphics Library Framework (GLFW)


[**Graphics Library Framework (GLFW)**](https://www.glfw.org/)은 **운영체제에서 OpenGL이 구동되는 창을 띄울 수 있게 도움을 주는 라이브러리**입니다. OpenGL은 주로 그림을 그리는 기능, 즉 프레임 버퍼를 채우는 기능만을 수행합니다. 하지만, 운영체제에서 OpenGL이 그린 그림을 창으로 띄우려면 추가적인 작업이 필요한데, 이 작업은 운영체제 네이티브 API를 이용해 운영체제마다 다르게 처리해야 하는 까다로운 작업입니다. GLFW는 이러한 운영체제별 부가 작업을 추상화하여 손쉽게 해결할 수 있는 라이브러리입니다. GLFW를 사용하려면 **`libglfw3-dev` 패키지를 설치**해야 합니다.

---

## 🖥️ Ubuntu에서 설치하기  

Ubuntu 환경에서는 다음 명령어를 실행하여 `libglfw3-dev` 패키지를 설치할 수 있습니다:

```bash
sudo apt install libglfw3-dev
```

설치가 완료되면 `pkg-config`를 이용하여 GLFW 라이브러리가 정상적으로 설치되었는지 확인할 수 있습니다:

```bash
pkg-config --modversion glfw3
```

위 명령어를 실행했을 때 **버전 정보(예: 3.3.10)**가 출력되면 설치가 정상적으로 완료된 것입니다. 🚀

---

✅ **이제 GLFW를 활용하여 프로젝트를 빌드할 준비가 되었습니다!**

