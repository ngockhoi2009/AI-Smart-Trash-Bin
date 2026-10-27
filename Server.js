const express = require('express');
const { GoogleGenAI } = require('@google/genai');
require('dotenv').config();

const app = express();
const port = 3000;

const ai = new GoogleGenAI({ 
    apiKey: process.env.GEMINI_API_KEY 
});

app.use(express.json({ limit: '10mb' }));
app.use(express.static('.'));

let type = 0;             
let yc = false;  
let xuly = false;    
app.get('/capture', (req, res) => {
    if (xuly || yc) {
        return res.status(409).json({ success: false, message: 'Hệ thống đang xử lý' });
    }
    
    type = 0;
    yc = true;
    console.log('-> ESP32 yêu cầu chụp ảnh!');
    res.json({ success: true });
});

app.get('/capture-status', (req, res) => {
    const yeucau = yc;
    yc = false; 
    res.json({ capture: yeucau });
});

app.post('/classify', async (req, res) => {
    if (xuly) {
        return res.status(409).json({ error: 'Đang xử lý ảnh, vui lòng đợi' });
    }

    const { image, mime } = req.body;
    if (!image || !mime) {
        return res.status(400).json({ error: 'Thiếu dữ liệu ảnh hoặc mime' });
    }

    xuly = true;
    type = 0;

    try {
        console.log('Đang gửi ảnh lên Gemini để phân loại...');
        const response = await ai.models.generateContent({
            model: 'gemini-3.5-flash', 
            contents: [
                {
                    inlineData: {
                        mimeType: mime,
                        data: image
                    }
                },
                `Phân loại vật rác trong ảnh này. 
                Chỉ trả về đúng định dạng:
                type=1 nếu là rác tái chế (chai nhựa, giấy, vỏ lon,...)
                type=2 nếu là rác không tái chế, rác hữu cơ hoặc không chắc chắn.
                Tuyệt đối không kèm theo chữ nào khác.`
            ]
        });

        const text = (response.text || '').trim();
        console.log('Kết quả từ AI:', text);
        if (text.includes('type=1')) {
            type = 1;
        } else {
            type = 2; 
        }

        console.log('-> Đã lưu kq: type =', type);
        res.json({ type: type });

    } catch (err) {
        console.error('Lỗi gọi Gemini API:', err.message);
        res.status(500).json({ error: 'Lỗi xử lý từ AI', details: err.message });
    } finally {
        xuly = false;
    }
});

app.get('/result', (req, res) => {
    const kq = type;
    if (type === 1 || type === 2) {
        type = 0;
    }
    
    res.json({ type: kq });
});

app.listen(port, '0.0.0.0', () => {
    console.log(`Server đang chạy`);
});