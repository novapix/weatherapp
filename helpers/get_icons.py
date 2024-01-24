from PIL import Image
import requests

ico_code = ["01", "02", "03", "04", "09", "10", "11", "13", "50"]
time = ["d", "n"]

for t in time:
    for i in ico_code:
        url = f"https://openweathermap.org/img/wn/{i}{t}.png"
        img = Image.open(requests.get(url, stream=True).raw)
        img.save(f"{i}{t}.png")
