import os

with open(
    os.path.join(os.path.dirname(__file__), os.pardir, "library.properties"), "r"
) as f:

    while True:
        line = f.readline()

        if len(line) == 0:
            break

        if line.startswith("name="):
            print(line.split("=")[1].strip().replace(' ', '_'))
            break
