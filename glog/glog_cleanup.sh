#!/bin/bash

shopt -s expand_aliases
alias echo='echo "$BASH_SOURCE:$LINENO:"' # $FUNCNAME

# Delete the oldest log files.
# Keep most recent log files with specified count.

# $1 - Log directory.
# $2 - Level of log file: INFO, WARNING, ERROR.
# $3 - Maximum count of log files to keep.
glog_cleanup() {
    local log_dir="$1"
    local log_level="$2"
    local max_count_keep="$3"

    if [[ -z "$log_dir" ]]; then
        echo "Error: Log directory not specified."
        return
    fi

    if [[ -z "$log_level" ]]; then
        echo "Error: Log level not specified."
        return
    fi

    if ! [[ "$max_count_keep" =~ ^[0-9]+$ ]] || (( max_count_keep < 0 )); then
        echo "Error: max count to keep must be non-negative integer."
        return
    fi

    # do not delete all of them
    minimal_count_keep="3"
    if (( max_count_keep < minimal_count_keep )); then
        max_count_keep="$minimal_count_keep"
    fi

    log_files=($(ls -1t "${log_dir}"/*.log."${log_level}".*))

    if (( ${#log_files[@]} > $max_count_keep )); then
        num_to_delete=$((${#log_files[@]} - $max_count_keep))

        # Delete the oldest log files!!!
        for (( i=0; i<num_to_delete; i++ )); do
            file="${log_files[$((max_count_keep + i))]}"
            echo "delete $file"
            rm "$file"
        done
    fi
}


# $ bash glog_cleanup.sh

LOG_DIR="./log" # path to the log files
MAX_COUNT_KEEP="3"

glog_cleanup "$LOG_DIR" "INFO" "$MAX_COUNT_KEEP"
glog_cleanup "$LOG_DIR" "WARNING" "$MAX_COUNT_KEEP"
glog_cleanup "$LOG_DIR" "ERROR" "$MAX_COUNT_KEEP"
