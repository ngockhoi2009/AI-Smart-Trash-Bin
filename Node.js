	

const express = require("express");
const app = express();
require("dotenv").config();

const { GoogleGenAI } = require("@google/genai");
const ai = new GoogleGenAI({
  apiKey: process.env.GEMINIAPIKEY
});
app.use(express.json({ limit: "15mb" }));
app.use(express.static("."));

let type = null;
let status = "start";
let capture = false;
let processing = false;

app.get("/capture", function(req, res) {
  if (processing || capture) {
    return res.json({ success: false });
  }
  type = null;
  status = "processing";
  capture = true;
  res.json({ success: true });
});

app.get("/capture-status", function(req, res) {
  let yeucau = capture;
  capture = false;
  res.json({
    capture: yeucau
  });
});

app.post("/classify", async function(req, res) {
  if (processing) {
    return res.json({ status: "processing" });
  }
  processing = true;
  type = null;
  status = "processing";

  try {
    let image = req.body.image64;
    let mime = req.body.mimetype;
    if (!image || !mime) throw new Error("Image Error");
    let response = await ai.models.generateContent({
      model: "gemini-3.5-flash-lite",
      contents: [
        {
          inlineData: {
            mimeType: mime,
            data: image
          }
        },
        {
          text: "Classify the trash in this image. Output only type=1 if it is recyclable (plastic bottle, paper, metal can, etc.), or type=2 if it is non-recyclable, organic, or uncertain. Do not include any other text, punctuation, or explanation."
        }
      ]
    });

    let text = (response.text || "").trim();
    if (text === "type=1") {
      type = 1;
    }
    else if (text === "type=2") {
      type = 2;
    }
    else {
      throw new Error("AI response error");
    }
    status = "done";
    res.json({
      type: type
    });
  }

  catch(error) {
    type = null;
    status = "error";
    res.json({
      status: "error",
      message: "Image ERROR"
    });
  }

  finally {
    processing = false;
  }
});

app.get("/result", function(req, res) {
  res.json({
    type: type,
    status: status
  });
});

app.listen(3000, function() {
  console.log("Server is running");
});
