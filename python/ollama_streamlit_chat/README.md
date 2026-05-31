# Ollama Streamlit Chat

一个本地 Ollama + Streamlit 聊天界面，布局参考 ChatGPT 的暗色侧边栏与居中输入框。

## 运行方式

1. 启动 Ollama：

```powershell
ollama serve
```

2. 拉取一个模型，例如：

```powershell
ollama pull qwen2.5:7b
```

3. 安装依赖并启动页面：

```powershell
cd "../ollama_streamlit_chat"
python -m pip install -r requirements.txt
python -m streamlit run app.py
```

## 可选配置

可以通过环境变量修改默认地址和模型：

```powershell
$env:OLLAMA_HOST = "http://localhost:11434"
$env:OLLAMA_MODEL = "qwen2.5:7b"
python -m streamlit run app.py
```

也可以在页面左侧设置栏里直接修改 Ollama 地址、模型、温度、Top P、上下文长度和系统提示词。
