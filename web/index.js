class waterfall {
    constructor(obj) {
        this.id = obj.id;
        this.imgUrls = obj.imgUrls;
        this.container = document.getElementById(this.id);
        this.container.className = 'forcenter';
        this.itemWidth = obj.itemWidth || 200; // 新增变量，默认为200
    }

    render() {
        let flag = 0;   // 用于检测每一张图片都加载完毕

        function checkImage(url) {
            return new Promise((resolve, reject) => {
                let img = new Image();
                img.src = url;
                img.onload = () => {
                    resolve(img);
                };
                img.onerror = () => {
                    console.log('图片加载失败');
                    reject();
                };
            });
        }

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
        function getMinH(arr) {
            let flag = {
                left: 0,
                top: 0,
                column: 0
            };

            arr.forEach((item, i) => {
                if (flag.top === 0) {
                    flag.top = item;
                } else {
                    if (flag.top > item) { 
                        flag.top = item;
                        flag.left = this.itemWidth * i; // 使用变量
                        flag.column = i;
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
        let itemNum = Math.floor(winW / this.itemWidth); // 修改为使用变量
        this.container.style.width = (itemNum * this.itemWidth) + 'px'; 

        let saveColumnHeight = [];  
        let items = document.querySelectorAll('.item');

        for (let i = 0; i < items.length; i++) {
            if (saveColumnHeight.length < itemNum) {
                saveColumnHeight[i] = items[i].offsetHeight;
                setDiv(items[i], this.itemWidth * i, 0);    
            } else {  
                let pos = getMinH.call(this, saveColumnHeight);    
                saveColumnHeight[pos.column] += items[i].offsetHeight;
                setDiv(items[i], pos.left, pos.top);    
            }
        }
    }
}
