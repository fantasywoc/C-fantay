import {convertFileSrc, invoke } from "@tauri-apps/api/tauri";
// import { arch } from '@tauri-apps/api/os';
// 剪切板内容获得
import { readText } from '@tauri-apps/api/clipboard';
// 文件打开对话框
import {open ,ask } from '@tauri-apps/api/dialog';

// import { open } from '@tauri-apps/api/dialog';




let greetInputEl: HTMLInputElement | null;
let greetMsgEl: HTMLElement | null;

let imgElement : HTMLImageElement|null;
async function greet() {
  if (greetMsgEl && greetInputEl) {
    // Learn more about Tauri commands at https://tauri.app/v1/guides/features/command
    greetMsgEl.textContent = await invoke("greet", {
      name: greetInputEl.value,
    });
    // const archName = await arch();
     await ask('This action cannot be reverted. Are you sure?', { title: 'Tauri', type: 'warning' });
    const clipboardText = await readText();

    const imagepath = await Getpath();
    greetMsgEl.textContent = await clipboardText;
  
    
    if (imgElement instanceof HTMLImageElement) {
      imgElement.src = await imagepath;// 替换成你想要的新图片路径
    }
    
  };
}




async function Getpath(): Promise<string> {
  let url_result = "/src/assets/typescript.svg";
  
  // 假设 open() 返回的是文件对象数组
  let files = await open({ multiple: true });

  if (Array.isArray(files) && files.length > 0) {
    const src = convertFileSrc(files[0]); // 假设 convertFileSrc 处理的是单个文件

    if (typeof src === 'string') {
      url_result = src;
    } else if (Array.isArray(src) ) {
      // 处理 `src` 为数组的情况，选取第一个值作为 `url_result`
      url_result = src[0];
    } else if (src === null) {
      // 处理 `src` 为 null 的情况，保持默认的 `url_result`
      console.error("convertFileSrc returned null.");
    } else {
      console.error("Unexpected value returned from convertFileSrc.");
    }
  } else {
    // 如果 `files` 不是数组，或者为空，则使用默认的 url_result
    console.error("No files or invalid file format.");
  }

  console.log(url_result);  // Optional: log the URL if needed
  
  return url_result;
}


// const yes = await ask('Are you sure?', 'Tauri');

window.addEventListener("DOMContentLoaded", () => {
  imgElement = document.querySelector(".showimage") as HTMLImageElement;
  greetInputEl = document.querySelector("#greet-input");
  greetMsgEl = document.querySelector("#greet-msg");
  document.querySelector("#greet-form")?.addEventListener("submit", (e) => {
    e.preventDefault();
    greet();


  });


});






