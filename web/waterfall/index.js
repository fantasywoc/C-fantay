const gridContainer = document.getElementById('grid-container');

// 模拟从服务器获取的数据
const items = Array.from({ length: 30 }, (_, i) => `Item ${i + 1}`);

// 动态创建项目
items.forEach(item => {
    const div = document.createElement('div');
    div.className = 'item';
    div.textContent = item;
    gridContainer.appendChild(div);
});
