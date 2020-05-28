const pageWidth = document.getElementsByTagName("canvas")[0].clientWidth;
const pageHeight = document.getElementsByTagName("canvas")[0].clientHeight;
const iterations = 8;
const startVectorLength = 75;
const startLinesCount = 3;
const vectorLengthIncrement = 15;
const linesCountIncrement = 1;
const start = new Point(pageWidth / 2, pageHeight / 2);

let iter, linesCount, vectorLength;

const resetAll = () => {
  iter = 0;
  linesCount = startLinesCount;
  vectorLength = startVectorLength;
};

const drawStar = () => {
  project.clear();

  ++iter;
  linesCount += linesCountIncrement;
  vectorLength += vectorLengthIncrement;

  if (iter > iterations) {
    resetAll();
  }

  for (let i = 0; i < linesCount; i++) {
    const path = new Path.Line(
      start,
      (start + [vectorLength, 0]).rotate((360 / linesCount) * i, start)
    );
    path.strokeColor = "black";
  }
};

resetAll();
drawStar();
setInterval(drawStar, 200);