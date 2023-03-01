legend = {}

with open("algorithms.cpp", encoding="utf-8") as file:
    lines = file.readlines()

    i = 0
    while i < len(lines):
        if lines[i].startswith("/// "):
            title = lines[i].strip().removeprefix("/// ")
            _link = lines[i + 1].strip().removeprefix("/// ")
            topics = lines[i + 2].strip().removeprefix("/// ").split(", ")
            line = i + 1

            for topic in topics:
                if topic not in legend:
                    legend[topic] = []
                legend[topic].append((title, line))

            i += 3
        else:
            i += 1

with open("README.md", "w", encoding="utf-8") as file:
    for topic in legend:
        file.write(f"* {topic}\n")

        for title, line in legend[topic]:
            file.write(f"   * [{title}](https://github.com/lucruum/tmp/blob/main/algorithms.cpp#L{line})\n")
            # file.write(f"   * [{title}](https://github.com/LoggerHead22/AlgoSection/blob/main/lucruum/algorithms.cpp#L{line})\n")
