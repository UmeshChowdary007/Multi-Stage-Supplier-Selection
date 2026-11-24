
const stageLabels = [
    "Raw Material Supplier",
    "Manufacturer",
    "Distributor",
    "Hospital"
];

async function runDP() {
    await executeAlgorithm("/api/dp", "dp");
}

async function runBruteForce() {
    await executeAlgorithm("/api/brute", "brute");
}

async function executeAlgorithm(endpoint, type) {
    const loading = document.getElementById("loading");
    const result = document.getElementById("result");

    loading.textContent = "Running C++ algorithm...";
    result.classList.add("hidden");

    try {
        const response = await fetch(endpoint);

        if (!response.ok) {
            throw new Error("Server returned an error.");
        }

        const data = await response.json();

        document.getElementById("resultTitle").textContent =
            type === "dp"
                ? "Dynamic Programming Results"
                : "Brute Force Results";

        document.getElementById("minimumCost").textContent =
            data.minimumCost;

        document.getElementById("optimalPath").textContent =
            data.path.join(" → ");

        document.getElementById("combinations").textContent =
            type === "dp"
                ? "DP computation"
                : data.combinations;

        const tableContainer =
            document.getElementById("dpTableContainer");

        if (type === "dp") {
            tableContainer.style.display = "block";

            const table = document.getElementById("dpTable");

            let html = `
                <tr>
                    <th>Stage</th>
                    <th>Option 1</th>
                    <th>Option 2</th>
                    <th>Option 3</th>
                </tr>
            `;

            data.table.forEach((row, index) => {
                html += `
                    <tr>
                        <th>${stageLabels[index]}</th>
                        <td>${row[0]}</td>
                        <td>${row[1]}</td>
                        <td>${row[2]}</td>
                    </tr>
                `;
            });

            table.innerHTML = html;
        } else {
            tableContainer.style.display = "none";
        }

        result.classList.remove("hidden");
        loading.textContent = "Algorithm executed successfully.";

        result.scrollIntoView({ behavior: "smooth" });

    } catch (error) {
        loading.textContent =
            "Could not connect to C++ server. Make sure server.exe is running.";

        console.error(error);
    }
}
