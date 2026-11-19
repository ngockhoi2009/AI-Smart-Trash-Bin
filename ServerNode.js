const express = require("express");
const app = express();
app.listen(3000, function() {
  console.log("Server is running");
});

const multer = require("multer");
app.post("/Classify", upload.single("image"), async function(req, res) {
  try {
    let image = req.file;
    if (!image) throw new Error("Image Error: 404");
    let image64 = image.buffer.toString("base64");

    let response = await ai.models.generateContent({
      model: "gemini-3.5-flash-lite",
      Contents: [
        {
          inclineData: {
            mimeType: mimetype,
            data: base64image
          }
        },
        { text: 'Phân loại vật rác trong ảnh này. Chỉ trả về đúng định dạng: type=1 nếu là rác tái chế (chai nhựa, giấy, vỏ lon,...) hay type=2 nếu là rác không tái chế, rác hữu cơ hoặc không chắc chắn.Tuyệt đối không kèm theo chữ nào khác.'}
      ]
    });
    let res = response.text;
    
  }
  


  catch() {
    console.log(error.message);
    res.send("Image ERROR");
  }
});






const ai = new GoogleGenAI({
  apiKey : process.env.GEMINIAPIKEY
});



