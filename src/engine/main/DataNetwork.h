#ifndef NETWORK_H
#define NETWORK_H

#include <avtSILRestriction.h>
#include <avtDataObject.h>
#include <avtDataObjectWriter.h>
#include <avtActor.h>
#include <avtPlot.h>
#include <Netnodes.h>
#include <string>
#include <vector>
#include <deque>

// ****************************************************************************
//  Class: DataNetwork
//
//  Purpose:
//      Stores a single AVT network.
//
//  Programmer: Jeremy Meredith
//  Creation:   September 29, 2000
//
//  Modifications:
//
//    Hank Childs, Wed Jan 17 10:26:34 PST 2001
//    Changed networks to be a database followed by a series of filters
//    followed by a plot.
//
//    Hank Childs, Tue Jun 12 14:42:09 PDT 2001
//    Changed type of filter to be the more arbitrary avtFilter.  Also added
//    a field for pipeline specifications.
//
//    Jeremy Meredith, Thu Jul 26 03:37:47 PDT 2001
//    Made networks use avtPluginFilters.
//
//    Jeremy Meredith, Fri Nov  9 10:22:05 PST 2001
//    Added a data specification, a plot type, and a network id.
//    Added a constructor and a method to release the used data.
//
//    Sean Ahern, Tue May 28 09:49:02 PDT 2002
//    Made this a tree.
//
//    Sean Ahern, Mon Dec 23 13:09:50 PST 2002
//    Okay, so it's not a tree.
//
//    Kathleen Bonnell, Wed Mar 31 16:53:03 PST 2004
//    Made some methods virtual, so this class can be inherited from. 
//
//    Mark C. Miller, Thu May 27 11:05:15 PDT 2004
//    Removed window attributes arg from GetActor method
//
//    Kathleen Bonnell, Thu Oct 21 15:55:46 PDT 2004 
//    Added ActorIsNull method. 
//
//    Mark C. Miller, Tue Jan  4 10:23:19 PST 2005
//    Changed id to nid
//    Added wid for window id 
//    Added methods to set/get window id
//
//    Kathleen Bonnell, Tue Mar 15 17:41:26 PST 2005 
//    Added clone.
//
// ****************************************************************************
class DataNetwork
{
public:
             DataNetwork(void);
    virtual ~DataNetwork(void);

    void SetNetID(int _id) { nid = _id; };
    void SetWinID(int _id) { wid = _id; };
    void SetPlottype(const std::string &type) { plottype = type; };
    virtual void SetPlot(avtPlot *_plot) { plot = _plot; };
    void SetTerminalNode(Netnode* t) {terminalNode = t;};
    void AddNode(Netnode *n) { nodeList.push_back(n); };
    void SetPipelineSpec(avtPipelineSpecification_p s) {pspec = s;};
    avtDataObject_p GetOutput(void) { return terminalNode->GetOutput(); };
    void SetDataSpec(avtDataSpecification_p s) {dspec = s;};
    void SetTime(int time_) {time = time_;};

    virtual void ReleaseData(void);

    avtDataSpecification_p& GetDataSpec() {return dspec;};
    avtPipelineSpecification_p GetPipelineSpec() {return pspec;};
    avtDataObjectWriter_p GetWriter(avtDataObject_p dob,
                                    avtPipelineSpecification_p pspec,
                                    WindowAttributes *atts);
    int GetNetID(void) const { return nid; };
    int GetWinID(void) const { return wid; };
    Netnode* GetTerminalNode(void) { return terminalNode; };
    virtual avtPlot_p GetPlot(void) { return plot; };
    avtActor_p GetActor(avtDataObject_p dob);
    bool ActorIsNull(void) { return (*plotActor == NULL); };
    void SetNetDB(NetnodeDB *d) { netdb = d; };
    NetnodeDB* GetNetDB(void) { return netdb; };
    virtual int GetTime() {return time;};
    std::string &GetPlottype(void) { return plottype; };
    std::vector<Netnode*>       &GetNodeList(void) { return nodeList; }; 

protected:
    int                         nid;
    int                         wid;
    Netnode                    *terminalNode;
    std::vector<Netnode*>       nodeList;
    avtDataSpecification_p      dspec;
    avtDataObjectWriter_p       writer;
    avtActor_p                  plotActor;
    double                      bgColor[3];
    double                      fgColor[3];
    avtPipelineSpecification_p  pspec;
    NetnodeDB*                  netdb;
    avtPlot_p                   plot;
    std::string                 plottype;
    int                         time;
    bool                        clone;
};

#endif
