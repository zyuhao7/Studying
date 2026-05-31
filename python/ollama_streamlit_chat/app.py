import json
import os
import uuid
import urllib.error
import urllib.request
from datetime import datetime

import streamlit as st


DEFAULT_HOST = os.getenv("OLLAMA_HOST", "http://localhost:11434")
DEFAULT_MODEL = os.getenv("OLLAMA_MODEL", "qwen2.5:7b")


st.set_page_config(
    page_title="Ollama Chat",
    page_icon="◉",
    layout="wide",
    initial_sidebar_state="expanded",
)


def inject_styles() -> None:
    st.markdown(
        """
        <style>
        :root {
            color-scheme: dark;
        }

        .stApp {
            background: #000000;
            color: #f4f4f5;
        }

        #MainMenu, footer, [data-testid="stHeader"] {
            visibility: hidden;
        }

        [data-testid="stSidebar"] {
            background: #050505;
            border-right: 1px solid #1c1c1f;
        }

        [data-testid="stSidebar"] [data-testid="stVerticalBlock"] {
            gap: 0.45rem;
        }

        [data-testid="stSidebar"] h1,
        [data-testid="stSidebar"] h2,
        [data-testid="stSidebar"] h3,
        [data-testid="stSidebar"] p,
        [data-testid="stSidebar"] label {
            color: #f6f6f7;
        }

        [data-testid="stSidebar"] .stButton > button {
            justify-content: flex-start;
            min-height: 2.25rem;
            border: 0;
            border-radius: 0.55rem;
            background: transparent;
            color: #efeff0;
            font-weight: 500;
            padding: 0.35rem 0.65rem;
        }

        [data-testid="stSidebar"] .stButton > button:hover {
            background: #2f2f2f;
            color: #ffffff;
        }

        [data-testid="stSidebar"] input,
        [data-testid="stSidebar"] textarea,
        [data-testid="stSidebar"] [data-baseweb="select"] > div {
            background: #111113;
            border-color: #27272a;
            color: #fafafa;
            border-radius: 0.55rem;
        }

        .block-container {
            max-width: 980px;
            padding-top: 1.15rem;
            padding-bottom: 8.8rem;
        }

        .topbar {
            display: flex;
            align-items: center;
            justify-content: space-between;
            margin-bottom: 1.5rem;
        }

        .brand-title {
            font-size: 1rem;
            font-weight: 700;
            color: #f7f7f8;
        }

        .top-actions {
            display: flex;
            gap: 0.55rem;
            align-items: center;
            color: #cfcfd4;
            font-size: 0.9rem;
        }

        .sidebar-logo {
            display: flex;
            align-items: center;
            gap: 0.6rem;
            margin: 0.4rem 0 0.75rem;
            font-size: 1.05rem;
            font-weight: 750;
        }

        .logo-dot {
            width: 1.65rem;
            height: 1.65rem;
            border-radius: 999px;
            display: inline-grid;
            place-items: center;
            background: #ffffff;
            color: #050505;
            font-weight: 800;
        }

        .nav-caption {
            margin: 1.05rem 0 0.35rem;
            color: #b9b9bf;
            font-size: 0.78rem;
            font-weight: 700;
        }

        .sidebar-note {
            color: #9d9da3;
            font-size: 0.78rem;
            line-height: 1.45;
            padding: 0.15rem 0.1rem 0.4rem;
        }

        .empty-state {
            min-height: 47vh;
            display: grid;
            place-items: end center;
            padding-bottom: 2.6rem;
        }

        .empty-state h1 {
            margin: 0;
            color: #f6f6f7;
            font-size: clamp(1.65rem, 3vw, 2.35rem);
            line-height: 1.15;
            text-align: center;
            font-weight: 700;
            letter-spacing: 0;
        }

        .quick-actions {
            display: flex;
            flex-wrap: wrap;
            justify-content: center;
            gap: 0.65rem;
            margin: 0 auto 1.1rem;
        }

        .quick-chip {
            border: 1px solid #2d2d32;
            border-radius: 999px;
            color: #f0f0f1;
            background: #050505;
            padding: 0.55rem 0.95rem;
            font-size: 0.9rem;
        }

        .status-card {
            border: 1px solid #2b2b30;
            background: #101012;
            border-radius: 0.55rem;
            padding: 0.72rem 0.78rem;
            color: #d7d7dc;
            font-size: 0.82rem;
            line-height: 1.5;
        }

        .status-pill {
            display: inline-flex;
            align-items: center;
            gap: 0.35rem;
            border-radius: 999px;
            padding: 0.15rem 0.52rem;
            margin-top: 0.35rem;
            background: #17351f;
            color: #a7f3b4;
            font-size: 0.75rem;
            font-weight: 700;
        }

        .status-pill.error {
            background: #3a1717;
            color: #fecaca;
        }

        [data-testid="stChatMessage"] {
            background: transparent;
            padding: 0.8rem 0;
        }

        [data-testid="stChatMessage"] [data-testid="stMarkdownContainer"] {
            color: #f4f4f5;
            font-size: 0.98rem;
            line-height: 1.72;
        }

        [data-testid="stChatMessage"]:has([aria-label="Chat message from user"]) {
            justify-content: flex-end;
        }

        [data-testid="stChatInput"] {
            max-width: 760px;
            margin: 0 auto 1.2rem;
        }

        [data-testid="stChatInput"] textarea {
            min-height: 3.35rem !important;
            border-radius: 1.65rem !important;
            background: #262626 !important;
            color: #ffffff !important;
            border: 1px solid #323236 !important;
            box-shadow: none !important;
            padding: 0.9rem 3.2rem 0.9rem 1.2rem !important;
        }

        [data-testid="stChatInput"] textarea::placeholder {
            color: #aaaab1;
        }

        [data-testid="stChatInput"] button {
            border-radius: 999px !important;
            background: #ffffff !important;
            color: #111111 !important;
        }

        .stAlert {
            border-radius: 0.55rem;
            border-color: #303036;
            background: #111113;
        }

        @media (max-width: 760px) {
            .block-container {
                padding-left: 1rem;
                padding-right: 1rem;
            }

            .top-actions {
                display: none;
            }

            .empty-state {
                min-height: 42vh;
                padding-bottom: 1.5rem;
            }
        }
        </style>
        """,
        unsafe_allow_html=True,
    )


def normalize_host(host: str) -> str:
    host = (host or DEFAULT_HOST).strip()
    if not host.startswith(("http://", "https://")):
        host = f"http://{host}"
    return host.rstrip("/")


@st.cache_data(ttl=20, show_spinner=False)
def fetch_models(host: str) -> tuple[list[str], str | None]:
    url = f"{normalize_host(host)}/api/tags"
    request = urllib.request.Request(url, method="GET")
    try:
        with urllib.request.urlopen(request, timeout=4) as response:
            data = json.loads(response.read().decode("utf-8"))
    except (urllib.error.URLError, TimeoutError, json.JSONDecodeError) as exc:
        return [], str(exc)

    models = [item.get("name", "") for item in data.get("models", [])]
    return [name for name in models if name], None


def stream_ollama_chat(
    *,
    host: str,
    model: str,
    messages: list[dict[str, str]],
    system_prompt: str,
    temperature: float,
    top_p: float,
    num_ctx: int,
):
    payload_messages = []
    if system_prompt.strip():
        payload_messages.append({"role": "system", "content": system_prompt.strip()})
    payload_messages.extend(messages)

    payload = {
        "model": model,
        "messages": payload_messages,
        "stream": True,
        "options": {
            "temperature": temperature,
            "top_p": top_p,
            "num_ctx": num_ctx,
        },
    }

    request = urllib.request.Request(
        f"{normalize_host(host)}/api/chat",
        data=json.dumps(payload).encode("utf-8"),
        headers={"Content-Type": "application/json"},
        method="POST",
    )

    try:
        with urllib.request.urlopen(request, timeout=120) as response:
            for raw_line in response:
                if not raw_line.strip():
                    continue
                data = json.loads(raw_line.decode("utf-8"))
                if data.get("error"):
                    raise RuntimeError(data["error"])
                token = data.get("message", {}).get("content", "")
                if token:
                    yield token
                if data.get("done"):
                    break
    except urllib.error.HTTPError as exc:
        detail = exc.read().decode("utf-8", errors="replace")
        raise RuntimeError(f"Ollama HTTP {exc.code}: {detail}") from exc
    except urllib.error.URLError as exc:
        raise RuntimeError(f"无法连接 Ollama: {exc.reason}") from exc
    except TimeoutError as exc:
        raise RuntimeError("Ollama 响应超时，请检查模型是否仍在加载。") from exc


def make_chat(title: str = "新聊天") -> dict:
    return {
        "id": uuid.uuid4().hex,
        "title": title,
        "messages": [],
        "created_at": datetime.now().strftime("%m-%d %H:%M"),
    }


def init_state() -> None:
    if "chats" not in st.session_state:
        chat = make_chat()
        st.session_state.chats = [chat]
        st.session_state.active_chat_id = chat["id"]

    if "host" not in st.session_state:
        st.session_state.host = DEFAULT_HOST
    if "model" not in st.session_state:
        st.session_state.model = DEFAULT_MODEL
    if "system_prompt" not in st.session_state:
        st.session_state.system_prompt = "你是一个简洁、可靠、善于解释代码的中文助手。"


def active_chat() -> dict:
    active_id = st.session_state.active_chat_id
    for chat in st.session_state.chats:
        if chat["id"] == active_id:
            return chat
    chat = st.session_state.chats[0]
    st.session_state.active_chat_id = chat["id"]
    return chat


def create_new_chat() -> None:
    chat = make_chat()
    st.session_state.chats.insert(0, chat)
    st.session_state.active_chat_id = chat["id"]


def title_from_prompt(prompt: str) -> str:
    compact = " ".join(prompt.strip().split())
    return compact[:18] + ("..." if len(compact) > 18 else "")


def render_sidebar() -> tuple[str, str, str, float, float, int]:
    with st.sidebar:
        st.markdown(
            """
            <div class="sidebar-logo">
                <span class="logo-dot">O</span>
                <span>Ollama Chat</span>
            </div>
            """,
            unsafe_allow_html=True,
        )

        if st.button("✎  新聊天", use_container_width=True):
            create_new_chat()
            st.rerun()

        search = st.text_input("搜索聊天", placeholder="搜索聊天", label_visibility="collapsed")

        st.markdown('<div class="nav-caption">最近</div>', unsafe_allow_html=True)
        visible_chats = [
            chat
            for chat in st.session_state.chats
            if not search or search.lower() in chat["title"].lower()
        ]

        for chat in visible_chats[:18]:
            prefix = "●  " if chat["id"] == st.session_state.active_chat_id else "   "
            if st.button(f"{prefix}{chat['title']}", key=f"chat-{chat['id']}", use_container_width=True):
                st.session_state.active_chat_id = chat["id"]
                st.rerun()

        st.markdown('<div class="nav-caption">设置</div>', unsafe_allow_html=True)
        host = st.text_input("Ollama 地址", value=st.session_state.host, help="默认是 http://localhost:11434")
        st.session_state.host = normalize_host(host)

        if st.button("刷新模型列表", use_container_width=True):
            fetch_models.clear()
            st.rerun()

        models, model_error = fetch_models(st.session_state.host)
        if models:
            default_index = models.index(st.session_state.model) if st.session_state.model in models else 0
            model = st.selectbox("模型", models, index=default_index)
        else:
            model = st.text_input("模型", value=st.session_state.model or DEFAULT_MODEL)

        st.session_state.model = model.strip() or DEFAULT_MODEL

        temperature = st.slider("Temperature", 0.0, 1.5, 0.7, 0.05)
        top_p = st.slider("Top P", 0.1, 1.0, 0.9, 0.05)
        num_ctx = st.slider("上下文长度", 1024, 32768, 8192, 1024)
        system_prompt = st.text_area("系统提示词", value=st.session_state.system_prompt, height=105)
        st.session_state.system_prompt = system_prompt

        if st.button("清空当前对话", use_container_width=True):
            active_chat()["messages"] = []
            active_chat()["title"] = "新聊天"
            st.rerun()

        status_class = "error" if model_error else ""
        status_text = "未连接" if model_error else "已连接"
        detail = model_error or f"当前模型：{st.session_state.model}"
        st.markdown(
            f"""
            <div class="status-card">
                Ollama 服务
                <div class="status-pill {status_class}">{status_text}</div>
                <div style="margin-top: .45rem;">{detail}</div>
            </div>
            """,
            unsafe_allow_html=True,
        )

        st.markdown(
            '<div class="sidebar-note">提示：先运行 <code>ollama serve</code>，再执行 <code>ollama pull 模型名</code>。</div>',
            unsafe_allow_html=True,
        )

    return (
        st.session_state.host,
        st.session_state.model,
        st.session_state.system_prompt,
        temperature,
        top_p,
        num_ctx,
    )


def render_topbar(model: str) -> None:
    st.markdown(
        f"""
        <div class="topbar">
            <div class="brand-title">ChatGPT ▾</div>
            <div class="top-actions">
                <span>✦ 本地 Ollama</span>
                <span>{model}</span>
            </div>
        </div>
        """,
        unsafe_allow_html=True,
    )


def render_empty_state() -> str | None:
    st.markdown(
        """
        <div class="empty-state">
            <h1>我们先从哪里开始呢？</h1>
        </div>
        """,
        unsafe_allow_html=True,
    )

    st.markdown('<div class="quick-actions">', unsafe_allow_html=True)
    cols = st.columns(3)
    prompts = [
        ("解释代码", "帮我用通俗的话解释这段代码，并指出可能的坑。"),
        ("写一段示例", "请给我写一个 Streamlit 聊天界面的最小示例。"),
        ("梳理思路", "我想做一个本地 AI 助手，请帮我拆成可执行步骤。"),
    ]
    selected = None
    for col, (label, prompt) in zip(cols, prompts):
        with col:
            if st.button(label, use_container_width=True):
                selected = prompt
    st.markdown("</div>", unsafe_allow_html=True)
    return selected


def render_messages(messages: list[dict[str, str]]) -> None:
    for message in messages:
        with st.chat_message(message["role"]):
            st.markdown(message["content"])


def handle_prompt(
    *,
    prompt: str,
    chat: dict,
    host: str,
    model: str,
    system_prompt: str,
    temperature: float,
    top_p: float,
    num_ctx: int,
) -> None:
    chat["messages"].append({"role": "user", "content": prompt})
    if chat["title"] == "新聊天":
        chat["title"] = title_from_prompt(prompt)

    with st.chat_message("user"):
        st.markdown(prompt)

    with st.chat_message("assistant"):
        placeholder = st.empty()
        answer = ""
        try:
            for token in stream_ollama_chat(
                host=host,
                model=model,
                messages=chat["messages"],
                system_prompt=system_prompt,
                temperature=temperature,
                top_p=top_p,
                num_ctx=num_ctx,
            ):
                answer += token
                placeholder.markdown(answer + "▌")
            placeholder.markdown(answer or "模型没有返回内容。")
        except RuntimeError as exc:
            answer = f"连接 Ollama 失败：{exc}"
            placeholder.error(answer)

    chat["messages"].append({"role": "assistant", "content": answer})


def main() -> None:
    inject_styles()
    init_state()

    host, model, system_prompt, temperature, top_p, num_ctx = render_sidebar()
    render_topbar(model)

    chat = active_chat()
    quick_prompt = None
    if not chat["messages"]:
        quick_prompt = render_empty_state()
    else:
        render_messages(chat["messages"])

    typed_prompt = st.chat_input("有问题，尽管问")
    prompt = typed_prompt or quick_prompt

    if prompt:
        handle_prompt(
            prompt=prompt,
            chat=chat,
            host=host,
            model=model,
            system_prompt=system_prompt,
            temperature=temperature,
            top_p=top_p,
            num_ctx=num_ctx,
        )


if __name__ == "__main__":
    main()
