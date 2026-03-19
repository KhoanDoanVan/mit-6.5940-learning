from pathlib import Path

def rename_images(folder_path):
    folder = Path(folder_path)

    exts = {".png", ".jpg", ".jpeg", ".webp"}
    files = [
        f for f in folder.iterdir()
        if f.is_file() and f.suffix.lower() in exts
    ]

    files = sorted(files, key=lambda f: (f.stat().st_ctime, f.stat().st_mtime))

    temp_files = []
    for i, f in enumerate(files):
        temp = folder / f"temp_{i}{f.suffix}"
        f.rename(temp)
        temp_files.append(temp)

    for i, f in enumerate(temp_files, start=1):
        new_name = folder / f"image{i}{f.suffix}"
        f.rename(new_name)

    return len(files)