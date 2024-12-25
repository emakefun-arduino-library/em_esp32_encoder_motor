import os
import json

examples_dir = os.path.join(os.path.dirname(__file__), os.pardir, "examples")
print(json.dumps(os.listdir(examples_dir)))
