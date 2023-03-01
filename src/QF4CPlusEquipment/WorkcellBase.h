#pragma once
#include <QObject>
#include "qf4cplusequipment_global.h"

class QF4CPLUSEQUIPMENT_EXPORT WorkcellBase :public QObject
{
	Q_OBJECT;
public:
    WorkcellBase()
    {
        m_Name = "Unnamed workcell";
        m_Description = "no description";
        m_Version = "n/a";
        m_Simulation = true;
    }

    virtual void Initialize() = 0;
    virtual void Startup() = 0;
    virtual void Dispose() = 0;

    // Properties ----------------------------------------------------------

    QString getName() {
        return m_Name;
    }


    bool getSimulation(){
        return m_Simulation;
    }

    //abstract IProcess MainProcess{ get; }
    //abstract IOManifest IOManifest{ get; }

    //    public string CurrentUser
    //{
    //    get
    //    {
    //        var username = "";
    //        if (UserAccessControl.CurrentUser != null)
    //        {
    //            username = UserAccessControl.CurrentUser.UserName;
    //        }
    //        return username;
    //    }
    //}

    //    public AccessLevel CurrentAccessLevel
    //    {
    //        get
    //        {
    //            var accessLevel = AccessLevel.Operator;
    //            if (UserAccessControl.CurrentUser != null)
    //            {
    //                accessLevel = UserAccessControl.GetAccessLevel(EquipmentType);
    //            }
    //            return accessLevel;
    //        }
    //    }

    //        // Methods -------------------------------------------------------------

    //    public abstract void RegisterPanels();

    //    public void SetEquipmentID(string equipID)
    //    {
    //        if (string.IsNullOrEmpty(equipID) || string.IsNullOrWhiteSpace(equipID))
    //            throw new ArgumentException();

    //        if (!string.IsNullOrEmpty(EquipmentID))
    //        {
    //            UserAccessControl.UnregisterEquipment(EquipmentID);
    //        }

    //        EquipmentID = equipID;
    //        UserAccessControl.RegisterEquipment(EquipmentID, EquipmentType);
    //    }
protected:
    void setName(QString name)
    {
        m_Name = name;
    }

    void setSimulation(bool simulation)
    {
        m_Simulation = m_Simulation;
    }
private:
    QString m_Name;

    int m_Slot;

    QString m_SlotName;

    QString m_EquipmentType;

    QString m_EquipmentID;

    QString m_Path;

    QString m_Description;

    QString m_Version;

    bool m_Simulation;

};

