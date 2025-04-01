import os
import shutil
import time
import tarfile
from datetime import datetime, timedelta

# 配置参数
LOG_DIR = "./logs"  # 日志文件存放目录
ARCHIVE_DIR = "./archives"  # 归档存放目录
LOG_RETENTION_DAYS = 1  # 超过 1 分钟的日志将被归档
ARCHIVE_RETENTION_DAYS = 1  # 超过 3 分钟的归档文件将被删除


def archive_old_logs():
    """查找并压缩旧日志文件"""
    now = time.time()
    cutoff_time = now - (LOG_RETENTION_DAYS * 1)  # 1 分钟前的时间戳

    if not os.path.exists(ARCHIVE_DIR):
        os.makedirs(ARCHIVE_DIR)  # 创建归档目录

    archive_name = f"{ARCHIVE_DIR}/logs_{datetime.now().strftime('%Y%m%d')}.tar.gz"

    with tarfile.open(archive_name, "w:gz") as tar:
        for filename in os.listdir(LOG_DIR):
            file_path = os.path.join(LOG_DIR, filename)
            if os.path.isfile(file_path) and os.path.getmtime(file_path) < cutoff_time:
                print(f"归档日志: {file_path}")
                tar.add(file_path, arcname=filename)
                os.remove(file_path)  # 归档后删除日志

    print(f"✅ 归档完成: {archive_name}")


def clean_old_archives():
    """删除超过 3 分钟的归档文件"""
    now = time.time()
    cutoff_time = now - (ARCHIVE_RETENTION_DAYS * 1)

    for filename in os.listdir(ARCHIVE_DIR):
        file_path = os.path.join(ARCHIVE_DIR, filename)
        if os.path.isfile(file_path) and os.path.getmtime(file_path) < cutoff_time:
            print(f"🗑️ 删除归档: {file_path}")
            os.remove(file_path)

    print("✅ 旧归档清理完成")


if __name__ == "__main__":
    print("📂 开始日志归档与清理...")
    archive_old_logs()
    clean_old_archives()
    print("🎯 任务完成！")
