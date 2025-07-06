const imageInput = document.getElementById('imageInput');
const uploadZone = document.getElementById('uploadZone');
const browseLink = document.getElementById('browseLink');
const algorithmSlider = document.getElementById('algorithmSlider');
const paletteSlider = document.getElementById('paletteSlider');
const algorithmValue = document.getElementById('algorithmValue');
const paletteValue = document.getElementById('paletteValue');
const parametersDiv = document.getElementById('parameters');
const ditherBtn = document.getElementById('ditherBtn');
const originalImg = document.getElementById('originalImg');
const ditheredImg = document.getElementById('ditheredImg');
const downloadBtn = document.getElementById('downloadBtn');
const statusDiv = document.getElementById('status');
const placeholder = document.getElementById('placeholder');
const originalPlaceholder = document.getElementById('originalPlaceholder');

let uploadedImageData = null;
let ditheredImageData = null;

const algorithms = ['floyd', 'atkinson', 'ordered', 'threshold', 'ascii'];
const algorithmNames = ['Floyd-Steinberg', 'Atkinson', 'Ordered (Bayer)', 'Threshold', 'ASCII'];
const palettes = ['grayscale', 'gameboy', 'nes', 'cga'];
const paletteNames = ['Grayscale', 'GameBoy', 'NES', 'CGA'];

function showStatus(msg, isError = false) {
    statusDiv.textContent = msg;
    statusDiv.style.color = isError ? '#b00' : '#666';
}

function updateAlgorithmDisplay() {
    const index = parseInt(algorithmSlider.value);
    algorithmValue.textContent = algorithmNames[index];
    updateParameters();
}

function updatePaletteDisplay() {
    const index = parseInt(paletteSlider.value);
    paletteValue.textContent = paletteNames[index];
    updateParameters();
}

function updateParameters() {
    parametersDiv.innerHTML = '';
    const algorithm = algorithms[parseInt(algorithmSlider.value)];
    const palette = palettes[parseInt(paletteSlider.value)];
    
    if (palette === 'grayscale') {
        const label = document.createElement('label');
        label.textContent = 'Grayscale Levels:';
        const input = document.createElement('input');
        input.type = 'range';
        input.id = 'grayscaleLevels';
        input.value = 4;
        input.min = 2;
        input.max = 16;
        input.className = 'slider';
        const valueSpan = document.createElement('span');
        valueSpan.textContent = '4';
        valueSpan.style.color = '#0078d7';
        valueSpan.style.fontWeight = '600';
        input.addEventListener('input', (e) => {
            valueSpan.textContent = e.target.value;
        });
        label.appendChild(input);
        label.appendChild(valueSpan);
        parametersDiv.appendChild(label);
    }
    
    if (algorithm === 'ordered') {
        const label = document.createElement('label');
        label.textContent = 'Bayer Size:';
        const input = document.createElement('input');
        input.type = 'range';
        input.id = 'bayerSize';
        input.value = 2;
        input.min = 1;
        input.max = 4;
        input.className = 'slider';
        const valueSpan = document.createElement('span');
        valueSpan.textContent = '2';
        valueSpan.style.color = '#0078d7';
        valueSpan.style.fontWeight = '600';
        input.addEventListener('input', (e) => {
            valueSpan.textContent = e.target.value;
        });
        label.appendChild(input);
        label.appendChild(valueSpan);
        parametersDiv.appendChild(label);
    }
    
    if (algorithm === 'threshold') {
        const label = document.createElement('label');
        label.textContent = 'Threshold:';
        const input = document.createElement('input');
        input.type = 'range';
        input.id = 'threshold';
        input.value = 0.5;
        input.min = 0.0;
        input.max = 1.0;
        input.step = 0.01;
        input.className = 'slider';
        const valueSpan = document.createElement('span');
        valueSpan.textContent = '0.5';
        valueSpan.style.color = '#0078d7';
        valueSpan.style.fontWeight = '600';
        input.addEventListener('input', (e) => {
            valueSpan.textContent = parseFloat(e.target.value).toFixed(2);
        });
        label.appendChild(input);
        label.appendChild(valueSpan);
        parametersDiv.appendChild(label);
    }
    
    if (algorithm === 'ascii') {
        const label = document.createElement('label');
        label.textContent = 'ASCII Set:';
        const select = document.createElement('select');
        select.id = 'asciiSet';
        [
            'Basic', 'Extended', 'Artistic', 'Simple', 'Shader', 'Retro', 'Advanced', 'Font8x8'
        ].forEach((name, idx) => {
            const opt = document.createElement('option');
            opt.value = idx;
            opt.textContent = name;
            select.appendChild(opt);
        });
        label.appendChild(select);
        parametersDiv.appendChild(label);
        
        const edgeLabel = document.createElement('label');
        edgeLabel.style.marginLeft = '12px';
        const edgeCheckbox = document.createElement('input');
        edgeCheckbox.type = 'checkbox';
        edgeCheckbox.id = 'detectEdges';
        edgeCheckbox.checked = true;
        edgeLabel.appendChild(edgeCheckbox);
        edgeLabel.appendChild(document.createTextNode(' Detect Edges'));
        parametersDiv.appendChild(edgeLabel);
    }
}

// Drag and Drop functionality
uploadZone.addEventListener('dragover', (e) => {
    e.preventDefault();
    uploadZone.classList.add('drag-over');
});

uploadZone.addEventListener('dragleave', (e) => {
    e.preventDefault();
    uploadZone.classList.remove('drag-over');
});

uploadZone.addEventListener('drop', (e) => {
    e.preventDefault();
    uploadZone.classList.remove('drag-over');
    
    const files = e.dataTransfer.files;
    if (files.length > 0) {
        const file = files[0];
        if (file.type.startsWith('image/')) {
            handleImageFile(file);
        } else {
            showStatus('Please drop an image file.', true);
        }
    }
});

browseLink.addEventListener('click', () => {
    imageInput.click();
});

imageInput.addEventListener('change', (e) => {
    const file = e.target.files[0];
    if (file) {
        handleImageFile(file);
    }
});

function handleImageFile(file) {
    const reader = new FileReader();
    reader.onload = function(evt) {
        uploadedImageData = evt.target.result;
        originalImg.src = uploadedImageData;
        originalImg.style.display = 'block';
        originalPlaceholder.style.display = 'none';
        showStatus('Image loaded successfully!');
    };
    reader.readAsDataURL(file);
}

// Slider event listeners
algorithmSlider.addEventListener('input', updateAlgorithmDisplay);
paletteSlider.addEventListener('input', updatePaletteDisplay);

// Initialize
window.addEventListener('DOMContentLoaded', () => {
    updateAlgorithmDisplay();
    updatePaletteDisplay();
});

ditherBtn.addEventListener('click', async () => {
    if (!uploadedImageData) {
        showStatus('Please upload an image first.', true);
        return;
    }
    
    showStatus('Processing...');
    
    // Prepare API request
    const algorithm = algorithms[parseInt(algorithmSlider.value)];
    const palette = palettes[parseInt(paletteSlider.value)];
    const params = {};
    
    if (palette === 'grayscale') {
        params.levels = parseInt(document.getElementById('grayscaleLevels').value) || 4;
    }
    if (algorithm === 'ordered') {
        params.bayer_size = parseInt(document.getElementById('bayerSize').value) || 2;
    }
    if (algorithm === 'threshold') {
        params.threshold = parseFloat(document.getElementById('threshold').value) || 0.5;
    }
    if (algorithm === 'ascii') {
        params.ascii_set = parseInt(document.getElementById('asciiSet').value) || 1;
        params.detect_edges = document.getElementById('detectEdges').checked;
    }
    
    // Convert image to base64 (strip data URL prefix)
    const base64Image = uploadedImageData.split(',')[1];
    const requestBody = {
        image: base64Image,
        palette: { type: palette, ...params },
        dither: { algorithm, ...params }
    };
    
    try {
        const response = await fetch('/api/dither', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(requestBody)
        });
        
        const result = await response.json();
        if (result.success && result.image) {
            ditheredImageData = 'data:image/png;base64,' + result.image;
            ditheredImg.src = ditheredImageData;
            ditheredImg.style.display = 'block';
            placeholder.style.display = 'none';
            downloadBtn.href = ditheredImageData;
            downloadBtn.style.display = 'inline-block';
            showStatus('Dithering complete!');
        } else {
            showStatus(result.error || 'Failed to process image.', true);
        }
    } catch (err) {
        showStatus('Error: ' + err.message, true);
    }
}); 