const char charts_js[] PROGMEM = R"rawliteral(

const line2Config = {
  type: 'line',
  data: {
    labels: ["-11 hrs","-10 hrs","-9 hrs","-8 hrs","-7 hrs","-6 hrs","-5 hrs","-4 hrs","-3 hrs","-2 hrs","-1 hrs","Ulitmo"],
    datasets: [
          {
        label: 'Maximo',
        fill: false,
        /**
         * These colors come from Tailwind CSS palette
         * https://tailwindcss.com/docs/customizing-colors/#default-color-palette
         */
        backgroundColor: '#7e3af2',
        borderColor: '#7e3af2',
        data: [%DLB0%, %DLB1%, %DLB2%,%DLB3%,%DLB4%,%DLB5%,%DLB6%,%DLB7%,%DLB8%,%DLB9%,%DLB10%,%DLB11%],
      },
      {
        label: 'Minimo',
        /**
         * These colors come from Tailwind CSS palette
         * https://tailwindcss.com/docs/customizing-colors/#default-color-palette
         */
        backgroundColor: '#0694a2',
        borderColor: '#0694a2',
        data: [%DLA0%, %DLA1%, %DLA2%,%DLA3%,%DLA4%,%DLA5%,%DLA6%,%DLA7%,%DLA8%,%DLA9%,%DLA10%,%DLA11%],
        fill: true,
      }, 
    ],
  },

  
  options: {
    responsive: true,
    /**
     * Default legends are ugly and impossible to style.
     * See examples in charts.html to add your own legends
     *  */
    legend: {
      display: false,
    },
    tooltips: {
      mode: 'index',
      intersect: false,
    },
    hover: {
      mode: 'nearest',
      intersect: true,
    },
    scales: {
      x: {
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Month',
        },
      },
      y: {
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Value',
        },
      },
    },
  },
}
const lineConfig = {
  type: 'line',
  data: {
    labels: ["-6:00", "-5:40", "-5:20", "-5:00","-4:40", "-4:20", "-4:00", "-3:40", "-3:20", "-3:00","-2:40", "-2:20", "-2:00","-1:40","-1:20","-1:00","-0:40","-0:20","0:00"],
    datasets: [
      {
        label: 'Temperatura',
        /**
         * These colors come from Tailwind CSS palette
         * https://tailwindcss.com/docs/customizing-colors/#default-color-palette
         */
        backgroundColor: '#06b6d4',
        borderColor: '#06b6d4',
        data: [%DLC0%, %DLC1%, %DLC2%,%DLC3%,%DLC4%,%DLC5%,%DLC6%,%DLC7%,%DLC8%,%DLC9%,%DLC10%, %DLC11%, %DLC12%,%DLC13%,%DLC14%,%DLC15%,%DLC16%,%DLC17%,%DLC18%,%DLC19%],
        fill: false,
      },

    ],
  },
  options: {
    responsive: true,
    /**
     * Default legends are ugly and impossible to style.
     * See examples in charts.html to add your own legends
     *  */
    legend: {
      display: false,
    },
    tooltips: {
      mode: 'index',
      intersect: false,
    },
    hover: {
      mode: 'nearest',
      intersect: true,
    },
    scales: {
      x: {
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Month',
        },
      },
      y: {
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Value',
        },
      },
    },
  },
}



// change this to the id of your chart element in HMTL
const lineCtx = document.getElementById('line2')
const lineCtx2 = document.getElementById('line')
window.myLine1 = new Chart(lineCtx, line2Config)
window.myLine2 = new Chart(lineCtx2, lineConfig)

)rawliteral";
