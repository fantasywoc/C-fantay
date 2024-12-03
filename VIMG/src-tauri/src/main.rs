

// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

// Learn more about Tauri commands at https://tauri.app/v1/guides/features/command
#[tauri::command]
fn greet(name: &str) -> String {
    format!("Hello, {}! You've been greeted from Rust!", name)
}


use tauri::Manager;
use std::fs;
use std::io::{BufReader, Cursor, Read};
use exif::{Reader};
use std::collections::HashMap;
use std::path::Path;
#[tauri::command]
fn ReadImageInfo<P: AsRef<Path>>(file_path: P) -> Result<HashMap<String, String>, Box<dyn std::error::Error>> {
    let file_path = file_path;
    // 读取EXIF信息
    let file = fs::File::open(&file_path)?;
    let mut reader = BufReader::new(file);
    let mut buf = Vec::new();

    // 读取文件内容到 buf
    reader.read_to_end(&mut buf)?;

    // println!("Read image success!");

    // 使用 Cursor 包装 buf，这样就可以实现 Seek trait
    let mut cursor = Cursor::new(buf);

    // 从 cursor 中读取 EXIF 数据
    let exif_data = Reader::new().read_from_container(&mut cursor)?;

    println!("Read image raw success!");
    let exif_tag = exif_data.fields();
    // print_type_of(&exif_tag);
    // 输出所有 EXIF 信息
    // 创建一个新的 HashMap
    let mut ImageInfo = HashMap::new();
    for field in exif_data.fields() {
        // println!("{:?}: {}", field.tag.to_string(), field.display_value().to_string());
        let tag_name = field.tag.to_string();
        let display_value = field.display_value().to_string();

        // 只插入感兴趣的标签
        if matches!(tag_name.as_str(), "LensModel" | "Model" | "StandardOutputSensitivity" | "FNumber" | "DateTimeOriginal" | "ExposureTime") {
            ImageInfo.insert(tag_name, display_value);
        }
    }
    Ok(ImageInfo) // 返回 HashMap
}


fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![greet])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
