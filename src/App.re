open State;

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let { seconds, currentPhase, isTicking, workTime, playTime } = state;

  React.useEffect0(() => {
    let timer = Js.Global.setInterval(() => dispatch(Tick), 1000);
    Some(() => Js.Global.clearInterval(timer));
  });

  <div className="container">
    <Header
      seconds
      currentPhase
      dispatch
    />
    <Timer
    seconds
    maxTime={
      switch (currentPhase) {
      | Work => workTime * 60
      | Play => playTime * 60
      }
    }
  />
    <TimerActions dispatch isTicking />
    <EditTime
      phase="Work"
      value={workTime}
      onChange={e => dispatch(SetTime(Work, e))}
    />
    <EditTime
      phase="Break"
      value={playTime}
      onChange={e => dispatch(SetTime(Play, e))}
    />
  </div>;
};







