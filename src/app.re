[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

type action = 
  | Increment
  | Decrement
  | SetTimer(Js.Global.intervalId)
  | StopTimer
  | UnsetTimer;

type state = {
  count: int,
  timer: option(Js.Global.intervalId),
};

let component = ReasonReact.reducerComponent("App");



let make = (~message, ~count=0, _children) => {
  ...component,
  reducer: (action, state) => switch action {
    | Increment => ReasonReact.Update({...state, count: state.count + 1})
    | Decrement => ReasonReact.Update({...state, count: state.count - 1})
    | SetTimer(timer) => ReasonReact.Update({...state, timer: Some(timer)})
    | StopTimer => ReasonReact.SideEffects(
      ({ state: { timer } }) => switch timer {
      | Some(t) => Js.Global.clearInterval(t)
      | None => ()
      })
    | UnsetTimer => ReasonReact.Update({...state, timer: None})
  },
  initialState: () => {
    count,
    timer: None
  },
  didMount: (self) => {
    self.reduce(() => SetTimer(Js.Global.setInterval(self.reduce((_) => Decrement), 1000)))();
    ReasonReact.NoUpdate;
  },
  render: self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" onClick={self.reduce(_event => Increment)} />
        <h2 onClick={self.reduce((_event) => StopTimer)}> (ReasonReact.stringToElement(message)) </h2>
      </div>
      <p className="App-intro">
        (ReasonReact.stringToElement("To get started, edit"))
        <code> (ReasonReact.stringToElement(" src/App.re ")) </code>
        (ReasonReact.stringToElement("and save to reload."))
      </p>

      <p>
        (ReasonReact.stringToElement(string_of_int(self.state.count)))
      </p>

      <Cell enabled=true />
    </div>
};
