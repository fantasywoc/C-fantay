class waterfall {
    constructor(obj) {
        this.id = obj.id;
        this.imgUrls = obj.imgUrls;
        this.container = document.getElementById(this.id);
        this.container.className = 'forcenter';
        this.itemWidth = obj.itemWidth || 200; // 新增变量，默认为200
    }

    render() {
        let flag = 0;   

                                    // (resolve, reject) => { ... }：这是一个箭头函数，它作为 Promise 构造函数的参数传入。这个函数会接收两个参数：
                                    //     resolve：一个函数，当异步操作成功时调用，用于将结果传递出去。
                                    //     reject：一个函数，当异步操作失败时调用，用于传递错误信息。

        function checkImage(url) {        // 用于检测每一张图片都加载完毕
            return new Promise((resolve, reject) => {
                let img = new Image();
                img.src = url;
                                    // img.onload
                                    // 定义：当图片成功加载完成时触发。
                                    // 用法：你可以在这个事件中执行一些操作，比如将图片添加到页面中，或更新应用的状态。

                img.onload = () => {
                    resolve(img);
                };
                                    // img.onerror
                                    // 定义：当图片加载失败时触发。
                                    // 用法：可以处理错误情况，比如显示一个默认图片，记录错误信息，或提示用户。

                img.onerror = () => {
                    console.log('图片加载失败');
                    reject();
                };
            });
        }
// ------------------------------------------------------------------------------------
// 代码段使用了 Array.prototype.map 方法来处理一个图像 URL 数组，并使用 checkImage 函数加载每个图像。        
// 1. this.imgUrls.map(...)

//     目的：对 this.imgUrls 中的每个元素（即每个图像的 URL）进行遍历，并对每个 URL 执行相应的操作。
//     参数：
//         item：当前遍历的 URL。
//         i：当前索引。

// 2. checkImage(item)

//     功能：调用 checkImage 函数，检查并加载当前 URL 的图像。这个函数返回一个 Promise。

// 3. .then((img) => {...})

//     处理成功：当图像加载成功时执行的回调。
//         打印 "图片正确"。
//         创建一个新的 div 元素，设置其类名为 'item'。
//         递增 flag（假设 flag 是在外部定义的，用于跟踪已加载的图像数量）。
//         将加载成功的图像 (img) 添加到 div，然后将该 div 添加到 this.container 中。

// 4. .catch(() => {...})

//     处理失败：当图像加载失败时执行的回调。
//         仅递增 flag，以确保计数保持一致。

// 5. .finally(() => {...})

//     最终处理：无论加载成功或失败，都会执行这个回调。
//         检查 flag 是否等于 this.imgUrls.length，如果相等，则表示所有图像都已处理完成，调用 this.resize() 方法。

// ------------------------------------------------------------------------------------
        this.imgUrls.map((item, i) => {
            checkImage(item).then((img) => {
                console.log("图片正确");
                let div = document.createElement('div');
                div.className = 'item';
                flag++;
                div.appendChild(img);
                this.container.appendChild(div);
            }).catch(() => {
                flag++;
            }).finally(() => {
                if (flag === this.imgUrls.length) {
                    this.resize();
                }
            });
        });

// creat  html style element
        let styleE = document.createElement('style');

        styleE.innerHTML = `
            div.item {
                position: absolute;
                transition: all .7s ease-in-out;  
                width: ${this.itemWidth}px; // 使用变量
                height: auto;
                padding: 5px;
                box-sizing: border-box; 
            }
            div.item img {
                width: 100%;
                height: auto;
            }
            .forcenter {
                position: relative;
                margin: auto;
            }`;
        this.container.appendChild(styleE);
    }

    resize() {
        function getMinHeight(arr) {
            let flag = {
                left: 0,
                top: 0,
                column: 0
            };

            arr.forEach((item, i) => {
                console.log(`item:${item};dfffi:${i}`);
                if (flag.top === 0) {
                    flag.top = item;
                } else {
                    if (flag.top > item) {   // 找出高度最小的那一列
                        flag.top = item;
                        flag.left = this.itemWidth * i; // 使用变量
                        flag.column = i;
                        console.log(`flag.left:${flag.left};flag.column:${flag.column}`);
                     
                    }
                }
            });

            return flag;
        }

        function setDiv(item, left, top) {
            item.style.left = left + 'px';
            item.style.top = top + 'px';
        }

        let winW = window.innerWidth;
        let itemNum = Math.floor(winW / this.itemWidth);                // 当每一个项的宽度都是固定的时候，需要计算出浏览器一行可以排列几个。
        this.container.style.width = (itemNum * this.itemWidth) + 'px'; // 用于居中的包裹盒子的宽度

        let saveColumnHeight = [];                                      // 定义一个数组，用于存储 每一列所有元素的高度 之和
        let items = document.querySelectorAll('.item');

        for (let i = 0; i < items.length; i++) {
            console.log(`--items[${i}]:${items[i]}`);
            if (saveColumnHeight.length < itemNum) {
                saveColumnHeight[i] = items[i].offsetHeight;           // 当布局的元素还没占满一行时，继续向数组中添加第一行第i列的高度
                setDiv(items[i], this.itemWidth * i, 0);               // 放置div
            } else {                                                   // 当已经占满一行时，就找出每一列的最小高度，然后当前的这个div放在高度最小的那一列
                let pos = getMinHeight.call(this, saveColumnHeight);   //去找高度最小的那一列
                saveColumnHeight[pos.column] += items[i].offsetHeight;
                setDiv(items[i], pos.left, pos.top);                   // 放置div
            }
        }
    }
}
