type phase =
  | Work
  | Play;

type state = {
  seconds: int,
  isTicking: bool,
  workTime: int,
  playTime: int,
  currentPhase: phase,
};

type action =
  | Start
  | Stop
  | Reset
  | Tick
  | TogglePhase
  | SetTime(phase, int);

let initialState = {
  seconds: 25 * 60,
  isTicking: false,
  workTime: 25,
  playTime: 5,
  currentPhase: Work,
};

let reducer = (state, action) => {
  switch (action) {
  | Start => {...state, isTicking: true}
  | Stop => {...state, isTicking: false}
  | Tick =>
    state.isTicking && state.seconds > 0
      ? {...state, seconds: state.seconds - 1} : state
  | Reset =>
    switch (state.currentPhase) {
    | Work => {...state, isTicking: false, seconds: state.workTime * 60}
    | Play => {...state, isTicking: false, seconds: state.playTime * 60}
    }
  | SetTime(phase, minutes) =>
    switch (phase) {
    | Work => {
        ...state,
        workTime: minutes,
        seconds:
          state.currentPhase === Work && !state.isTicking
            ? minutes * 60 : state.seconds,
      }
    | Play => {
        ...state,
        playTime: minutes,
        seconds:
          state.currentPhase === Play && !state.isTicking
            ? minutes * 60 : state.seconds,
      }
    }
  | TogglePhase =>
    switch (state.currentPhase) {
    | Work => {
        ...state,
        currentPhase: Play,
        seconds: state.playTime * 60,
        isTicking: true,
      }
    | Play => {
        ...state,
        currentPhase: Work,
        seconds: state.workTime * 60,
        isTicking: true,
      }
    }
  };
};




