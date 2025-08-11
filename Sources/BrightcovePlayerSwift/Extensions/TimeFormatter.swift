//
// TimeFormatter.swift
// BrightcovePlayerSwift
//
// Copyright (c) 2025 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

import Foundation

/// Utility for formatting time intervals for video playback
public enum TimeFormatter {
    
    /// Format a time interval as MM:SS or HH:MM:SS
    /// - Parameter timeInterval: The time interval in seconds
    /// - Returns: Formatted time string
    public static func formatTime(_ timeInterval: TimeInterval) -> String {
        guard !timeInterval.isNaN && !timeInterval.isInfinite else {
            return "--:--"
        }
        
        let hours = Int(timeInterval) / 3600
        let minutes = (Int(timeInterval) % 3600) / 60
        let seconds = Int(timeInterval) % 60
        
        if hours > 0 {
            return String(format: "%d:%02d:%02d", hours, minutes, seconds)
        } else {
            return String(format: "%02d:%02d", minutes, seconds)
        }
    }
    
    /// Format a time interval with a specific format
    /// - Parameters:
    ///   - timeInterval: The time interval in seconds
    ///   - format: The desired format
    /// - Returns: Formatted time string
    public static func formatTime(_ timeInterval: TimeInterval, format: TimeFormat) -> String {
        guard !timeInterval.isNaN && !timeInterval.isInfinite else {
            return format.placeholderString
        }
        
        let hours = Int(timeInterval) / 3600
        let minutes = (Int(timeInterval) % 3600) / 60
        let seconds = Int(timeInterval) % 60
        
        switch format {
        case .short:
            return String(format: "%d:%02d", minutes, seconds)
        case .standard:
            if hours > 0 {
                return String(format: "%d:%02d:%02d", hours, minutes, seconds)
            } else {
                return String(format: "%02d:%02d", minutes, seconds)
            }
        case .long:
            return String(format: "%d:%02d:%02d", hours, minutes, seconds)
        case .verbose:
            var components: [String] = []
            if hours > 0 {
                components.append("\(hours)h")
            }
            if minutes > 0 {
                components.append("\(minutes)m")
            }
            if seconds > 0 || components.isEmpty {
                components.append("\(seconds)s")
            }
            return components.joined(separator: " ")
        }
    }
    
    /// Get remaining time from current time and duration
    /// - Parameters:
    ///   - currentTime: Current playback time
    ///   - duration: Total duration
    /// - Returns: Formatted remaining time string (with minus sign)
    public static func formatRemainingTime(currentTime: TimeInterval, duration: TimeInterval) -> String {
        let remaining = duration - currentTime
        return "-" + formatTime(remaining)
    }
    
    /// Format time with milliseconds precision
    /// - Parameter timeInterval: The time interval in seconds
    /// - Returns: Formatted time string with milliseconds
    public static func formatTimeWithMilliseconds(_ timeInterval: TimeInterval) -> String {
        guard !timeInterval.isNaN && !timeInterval.isInfinite else {
            return "--:--.---"
        }
        
        let hours = Int(timeInterval) / 3600
        let minutes = (Int(timeInterval) % 3600) / 60
        let seconds = Int(timeInterval) % 60
        let milliseconds = Int((timeInterval.truncatingRemainder(dividingBy: 1)) * 1000)
        
        if hours > 0 {
            return String(format: "%d:%02d:%02d.%03d", hours, minutes, seconds, milliseconds)
        } else {
            return String(format: "%02d:%02d.%03d", minutes, seconds, milliseconds)
        }
    }
}

// MARK: - TimeFormat

public enum TimeFormat {
    case short      // M:SS
    case standard   // MM:SS or H:MM:SS
    case long       // H:MM:SS (always show hours)
    case verbose    // 1h 23m 45s
    
    var placeholderString: String {
        switch self {
        case .short: return "-:--"
        case .standard: return "--:--"
        case .long: return "-:--:--"
        case .verbose: return "--"
        }
    }
}

// MARK: - Extensions

public extension TimeInterval {
    
    /// Format this time interval using the default format
    var formattedTime: String {
        TimeFormatter.formatTime(self)
    }
    
    /// Format this time interval using a specific format
    /// - Parameter format: The desired format
    /// - Returns: Formatted time string
    func formattedTime(format: TimeFormat) -> String {
        TimeFormatter.formatTime(self, format: format)
    }
    
    /// Get a human-readable description of the duration
    var durationDescription: String {
        TimeFormatter.formatTime(self, format: .verbose)
    }
}

// MARK: - Progress Utilities

public enum ProgressFormatter {
    
    /// Format progress as a percentage
    /// - Parameter progress: Progress value from 0.0 to 1.0
    /// - Returns: Formatted percentage string
    public static func formatProgress(_ progress: Double) -> String {
        let percentage = Int(progress * 100)
        return "\(percentage)%"
    }
    
    /// Format progress with current time and duration
    /// - Parameters:
    ///   - currentTime: Current playback time
    ///   - duration: Total duration
    /// - Returns: Formatted progress string like "1:23 / 4:56"
    public static func formatProgressWithTime(currentTime: TimeInterval, duration: TimeInterval) -> String {
        let current = TimeFormatter.formatTime(currentTime)
        let total = TimeFormatter.formatTime(duration)
        return "\(current) / \(total)"
    }
    
    /// Calculate progress percentage from current time and duration
    /// - Parameters:
    ///   - currentTime: Current playback time
    ///   - duration: Total duration
    /// - Returns: Progress value from 0.0 to 1.0
    public static func calculateProgress(currentTime: TimeInterval, duration: TimeInterval) -> Double {
        guard duration > 0 && !duration.isNaN && !duration.isInfinite else {
            return 0.0
        }
        
        let progress = currentTime / duration
        return max(0.0, min(1.0, progress))
    }
}