#!/usr/bin/env python3
"""
PCMAC results analysis — produces NoRIS vs WithRIS comparison plots.
Run from ~/my_pcmac_sim/:
    python3 scripts/analyze_results.py
"""

import subprocess
import pandas as pd
import matplotlib.pyplot as plt
import os

RESULTS_DIR = "results"
OUTPUT_DIR  = "plots"
os.makedirs(OUTPUT_DIR, exist_ok=True)


def extract(metric_filter, output_csv):
    """Use opp_scavetool to export a scalar metric to CSV."""
    cmd = [
        "opp_scavetool", "export",
        "-f", f"name =~ {metric_filter}",
        f"{RESULTS_DIR}/*.sca",
        "-o", output_csv
    ]
    subprocess.run(cmd, check=True)
    return pd.read_csv(output_csv)


def plot_metric(df, metric_col, ylabel, title, filename):
    """Plot NoRIS vs WithRIS across vehicle counts."""
    fig, ax = plt.subplots(figsize=(8, 5))

    for cfg_label in ["NoRIS", "WithRIS"]:
        subset = df[df["config"].str.contains(cfg_label, na=False)]
        if subset.empty:
            continue
        # Group by numVehicles and average across repetitions
        grouped = subset.groupby("numVehicles")[metric_col].mean().reset_index()
        ax.plot(grouped["numVehicles"], grouped[metric_col],
                marker="o", label=cfg_label)

    ax.set_xlabel("Number of Vehicles (N)")
    ax.set_ylabel(ylabel)
    ax.set_title(title)
    ax.legend()
    ax.grid(True, linestyle="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(os.path.join(OUTPUT_DIR, filename), dpi=150)
    plt.close()
    print(f"Saved: {OUTPUT_DIR}/{filename}")


if __name__ == "__main__":
    # ── Delay ────────────────────────────────────────────────────────────
    delay_df = extract("delay:mean", "/tmp/delay.csv")
    plot_metric(
        delay_df,
        metric_col="value",
        ylabel="Avg Delay (s)",
        title="PCMAC: Emergency Message Delay — NoRIS vs WithRIS",
        filename="delay_comparison.png"
    )

    # ── Throughput ───────────────────────────────────────────────────────
    tput_df = extract("throughput:mean", "/tmp/throughput.csv")
    plot_metric(
        tput_df,
        metric_col="value",
        ylabel="Throughput",
        title="PCMAC: Channel Throughput — NoRIS vs WithRIS",
        filename="throughput_comparison.png"
    )

    # ── Emergency Service Rate (PDR proxy) ────────────────────────────────
    esr_df = extract("emergencyServiced:sum", "/tmp/esr.csv")
    plot_metric(
        esr_df,
        metric_col="value",
        ylabel="Emergency Messages Serviced",
        title="PCMAC: Emergency Service Rate — NoRIS vs WithRIS",
        filename="emergency_service_comparison.png"
    )

    print("\nAll plots saved to:", OUTPUT_DIR)
