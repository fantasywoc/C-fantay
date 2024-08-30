# C-fantay

study

sublime C++ 配置
```
{
  "cmd": [
    "bash", "-c", "g++ -std=c++17 -Wall \"${file}\" -o \"${file_path}/${file_base_name}\" && \"${file_path}/${file_base_name}\""
  ],
  "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
  "working_dir": "${file_path}",
  "selector": "source.c, source.c++",
  "variants": [
    {
      "name": "Run",
      "cmd": [
        "bash", "-c", "g++ -std=c++17 \"${file}\" -o \"${file_path}/${file_base_name}\" && \"${file_path}/${file_base_name}\""
      ]
    },
    {
      "name": "Run In Terminal",
      "cmd": [
        "gnome-terminal", "--", "bash", "-c", "g++ -std=c++17 \"${file}\" -o \"${file_path}/${file_base_name}\" && \"${file_path}/${file_base_name}\" && read -p '\nPress any key to continue...'"
      ]
    }
  ]
}


```



learning
