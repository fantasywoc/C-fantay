use std::fs;
use std::io::{BufReader, Cursor, Read};
use exif::{Reader};
mod Carmera_info::image_info;

fn print_type_of<T>(value: &T) {  
    println!("Type of value: {}", std::any::type_name::<T>());  
}

enum Make {  
    Make,  
    Model,  
    ExposureTime,  
    ISO,
    ExposureProgram,
    FNumber,
}  
impl Make {  
    fn to_string(&self) -> &'static str {  
        match self {  
            Make::Make => "Make",  
            Make::Model => "Model",  
            Make::ExposureTime => "ExposureTime",  
            Make::ISO => "StandardOutputSensitivity",
            Make::ExposureProgram => "ExposureProgram",
            Make::FNumber => "FNumber",
        }  
    }  
}  

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let file_path = "/home/kf/Pictures/20241004_P1012764.JPG";

     // 读取EXIF信息
     let file = fs::File::open(&file_path)?;
     let mut reader = BufReader::new(file);
     let mut buf = Vec::new();
 
     // 读取文件内容到 buf
     reader.read_to_end(&mut buf)?;
 
     println!("Read image success!");
 
     // 使用 Cursor 包装 buf，这样就可以实现 Seek trait
     let mut cursor = Cursor::new(buf);
 
     // 从 cursor 中读取 EXIF 数据
     let exif_data = Reader::new().read_from_container(&mut cursor)?;
 
     println!("Read image raw success!");
     let exif_tag = exif_data.fields();
     print_type_of(&exif_tag);
     // 输出所有 EXIF 信息
    
    let ImageInfo=Carmera_info::image_info{
        name : "names".to_string(),
        Make : "make".to_string(),

    };
    for field in exif_data.fields() {
        if Make::Make.to_string()==field.tag.to_string() {
            println!("{:?}: {}", field.tag.to_string(), field.display_value().to_string())
        } else if Make::Model.to_string()==field.tag.to_string() {
            println!("{:?}: {}", field.tag.to_string(), field.display_value().to_string())
        } else if Make::ISO.to_string()==field.tag.to_string(){
            println!("{:?}: {}", field.tag.to_string(), field.display_value().to_string())
        } else if Make::FNumber.to_string()==field.tag.to_string(){
            println!("{:?}: {}", field.tag.to_string(), field.display_value().to_string())
        }
        
     }
    


     Ok(())
}