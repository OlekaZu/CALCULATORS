const graph = document.getElementById('graphChart')
const xMin = document.getElementById('xMin')
const xMax = document.getElementById('xMax')
const yMin = document.getElementById('yMin')
const yMax = document.getElementById('yMax')



const graphConfig = {
    type: 'line',
    options: {
        spanGaps: true,
        plugins: {
            legend: {
                display: false
            }
        },
        scales: {
            x: {
                display: true
            },
            y: {
                display: true,
                min: yMin.value,
                max: yMax.value
            }
        }
    },
    data: {
        datasets: [{
            tension: 0.4,
            pointRadius: 0,
            fill: false,
            spanGaps: true,
            borderColor: "#E2687D"
        }]
    }
}

const chart = new Chart(graph, graphConfig)

window.onload = function () {
    document.getElementById('inputFormula').value = localStorage.getItem('transferFormula')
    localStorage.clear()
    drawGraph();
}

function drawGraph() {
    let datapost = {
        inputFormula: $("#inputFormula").val(),
        xMin: xMin.value,
        xMax: xMax.value,
        yMin: yMin.value,
        yMax: yMax.value
    }

    $.ajax({
        type: "POST",
        url: "/Home/Graph",
        data: datapost,
        success: updateGraph,
        error: () => {
            alert('Something wrong')
        }
    })
}

function updateGraph(data) {
    let labels = []
    for (let i = 0; i < data.length; i++) {
        labels[i] = Math.round((data[i].x + Number.EPSILON) * 100) / 100
    }
    chart.data.labels = labels
    chart.data.datasets[0].data = data
    chart.update()
}

function updateYAxe() {
    chart.options.scales.y = {
        min: yMin.value,
        max: yMax.value
    }
    chart.update()
}
