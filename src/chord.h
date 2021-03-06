/*
 * File:   	chord.h
 * Author: 	Sam Rappl and Jacob Inkrote
 *
 */

#ifndef CHORD_H
#define CHORD_H

#include <vector>
#include "constants.h"
#include "event.h"

/**
 * A Chord is an object that represents several music notes with the same duration.
 */
struct Chord: public Event {

    /**
     * Constructs a Chord object with a c major chord and the duration of a quarter note.
     */
    Chord(): pitches(c_major_chord), duration(quarter_note), triplet(0),
            dotted(0), double_dotted(0), staccato(0), tenuto(0),
            accent(0), fermata(0), tied(0), slurred(0){}

    /**
     * Constructs a Chord object with specified pitches and duration. Pitch and Duration
     * parameters are required, others are optional.
     *
     * @param pitch The pitches of the chord.
     * @param duration The duration of the chord.
     * @param triplet Whether the chord is in a triplet or not.
     * @param dotted Whether the chord is dotted or not.
     * @param double_dotted Whether the chord is double dotted or not.
     * @param staccato Whether the chord is staccato or not.
     * @param tenuto Whether the chord is tenuto or not.
     * @param accent Whether the chord is accented or not.
     * @param fermata Whether the chord is to be held or not.
     * @param tied Whether the chord is tied to the next chord.
     * @param slurred Whether the chord is slurred to the next chord.
     */
    Chord(std::vector<int> pitches, int duration, int triplet = 0,
            int dotted = 0, int double_dotted = 0, int staccato = 0,
            int tenuto = 0, int accent = 0, int fermata = 0,
            int tied = 0, int slurred = 0) : pitches(pitches),
            duration(duration), triplet(triplet), dotted(dotted),
            double_dotted(double_dotted), staccato(staccato),
            tenuto(tenuto), accent(accent), fermata(fermata),
            tied(tied), slurred(slurred){}

    /**
     * Adds a dot to the chord (which turns on the dotted flag and increases the duration
     * of the chord by 1/2 of its original duration, unless it is already dotted, in which
     * case, it double dots the chord by increasing its duration by 7/6 its original duration.
     *
     * @return Whether the chord was dotted.
     */
    bool dot() {
        if (!dotted) {
            if (duration == one_twenty_eighth_note) {
                return false;
            } else {
                dotted = true;
                duration *= 1.5;
            }
            return true;
        } else if (dotted && !double_dotted) {
            if (duration == dotted_sixty_fourth_note) {
                return false;
            } else {
                double_dotted = true;
                duration /= 6;
                duration *= 7;
            }
            return true;
        }
        return false;
    }

    /**
     * Adds two dots to the chord, turning its duration into 7/4 its original duration.
     *
     * @return Whether the chord was double dotted.
     */
    bool double_dot() {
        if (dotted) {
            return false;
        } else if (duration == one_twenty_eighth_note || duration == sixty_fourth_note) {
            return false;
        } else {
            dotted = true;
            double_dotted = true;
            duration /= 4;
            duration *= 7;
        }
        return true;
    }

    /**
     * Puts the chord in a triplet by turning on the triplet flag and making the chord's
     * duration 2/3 its original duration.
     *
     * @return Whether the chord was added to a triplet.
     */
    bool put_in_triplet() {
        if (triplet) {
            return false;
        } else {
            triplet = true;
            duration /= 3;
            duration *= 2;
        }
        return true;
    }

    /**
     * Moves the chord up one octave.
     *
     * @return Whether the chord was moved up an octave.
     */
    bool add_octave() {
        if (pitches.size() == 0 || pitches[pitches.size()-1] + 12 > 126) {
            return false;
        }
        for (int i = 0; i < pitches.size(); i++) {
            pitches[i] += 12;
        }
        return true;
    }

    /**
     * Moves the chord down one octave.
     *
     * @return Whether the chord was moved down an octave.
     */
    bool drop_octave() {
        if (pitches.size() == 0 || pitches[0] - 12 < 0) {
            return false;
        }
        for (int i = 0; i < pitches.size(); i++) {
            pitches[i] -= 12;
        }
        return true;
    }

    /**
     * Moves the bottom note of the chord up one octave.
     *
     * @return Whether the chord could be inverted.
     */
    bool invert() {
        if (pitches.size() < 2 || pitches[0] + 12 > 126) {
            return false;
        }
        pitches.push_back(pitches[0] + 12);
        pitches.erase(pitches.begin());
        return true;
    }
    
    /**
     * Returns true if this chord is equivalent to the chord passed in.
     *
     * @param chord The chord to compare
     * @return true if this chord is the same as the chord passed in.
     */
    bool equals(Chord *chord) {
        if (pitches.size() != chord->pitches.size()) {
            return false;
        }
        else {
            for (int i = 0; i < pitches.size(); i++) {
                if (pitches[i] != chord->pitches[i]) {
                    return false;
                }
            }
        }
        if (duration != chord->duration) {
            return false;
        }
        if (triplet != chord->triplet) {
            return false;
        }
        if (dotted != chord->dotted) {
            return false;
        }
        if (double_dotted != chord->double_dotted) {
            return false;
        }
        if (staccato != chord->staccato) {
            return false;
        }
        if (tenuto != chord->tenuto) {
            return false;
        }
        if (accent != chord->accent) {
            return false;
        }
        if (fermata != chord->fermata) {
            return false;
        }
        if (tied != chord->tied) {
            return false;
        }
        if (slurred != chord->slurred) {
            return false;
        }
        return true;
    }
    
    std::vector<int> pitches;
    int duration;
    bool triplet;
    bool dotted;
    bool double_dotted;
    bool staccato;
    bool tenuto;
    bool accent;
    bool fermata;
    bool tied;
    bool slurred;
};

#endif /* CHORD_H */
